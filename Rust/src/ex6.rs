use std::{
    cell::RefCell,
    cmp,
    fmt::{Debug, Display},
    mem::replace,
    ptr,
    rc::{Rc, Weak},
};

#[derive(Debug, Clone)]
pub struct AVLNode<T> {
    element: T,
    pub left: Option<Box<AVLNode<T>>>,
    right: Option<Box<AVLNode<T>>>,
    // still not working correctly
    pub parent: *const Box<AVLNode<T>>,
    node_height: usize,
}

impl<T> AVLNode<T> {
    fn new(key: T) -> AVLNode<T> {
        AVLNode {
            element: key,
            node_height: 1,
            left: None,
            right: None,
            parent: ptr::null::<Box<AVLNode<T>>>(),
        }
    }
}

impl<T: std::fmt::Display> Display for AVLNode<T> {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        let el = &self.element;
        let height = self.node_height;
        write!(f, "({el} -> height: {height})")
    }
}

#[derive(Debug, Clone)]
pub struct MyAVLTree<T> {
    pub root: Option<Box<AVLNode<T>>>,
    pub(self) no_nodes: usize,
}

impl<T: std::fmt::Display + Ord + Debug + Clone> MyAVLTree<T> {
    fn get_height(&self, node: &Option<Box<AVLNode<T>>>) -> usize {
        match node {
            Some(node) => node.node_height,
            None => 0,
        }
    }

    fn update_height(&self, node: &mut Box<AVLNode<T>>) {
        let max = cmp::max(self.get_height(&node.left), self.get_height(&node.right));
        node.node_height = 1 + max;
    }

    fn get_balance(&self, node: &Option<&Box<AVLNode<T>>>) -> i8 {
        if node.is_none() {
            return 0;
        }
        let node = node.unwrap();

        let r_height = self.get_height(&node.right);
        let l_height = self.get_height(&node.left);

        let diff = r_height as isize - l_height as isize;

        if diff > 1 {
            return -1;
        }
        if diff < -1 {
            return 1;
        }

        return 0;
    }

    fn get_minimum<'a>(&self, node: &'a Box<AVLNode<T>>) -> &'a Box<AVLNode<T>> {
        let mut current = node;
        while current.left.is_some() {
            current = node.left.as_ref().unwrap();
        }

        return current;
    }

    fn right_rotate(&self, mut y: Box<AVLNode<T>>) -> Box<AVLNode<T>> {
        println!("right");

        let mut x = y.left.take().expect("AVL BROKEN");
        let mut t2 = x.right.take();

        // let mut t2 = replace(&mut y.left, t2);
        if t2.is_some() {
            let t2 = t2.as_mut().unwrap();
            let ptr = &y as *const Box<AVLNode<T>>;
            t2.parent = ptr;
            println!("{:#?} - {:#?}", t2.parent, ptr);
        }

        y.left = t2;

        x.parent = y.parent;
        println!("{:#?} - {:#?}", x.parent, y.parent);
        y.parent = &x as *const Box<AVLNode<T>>;
        println!("{:#?} - {:#p}\n", y.parent, x);

        self.update_height(&mut y);
        x.right = Some(y);

        self.update_height(&mut x);

        return x;
    }

    fn left_rotate(&self, mut x: Box<AVLNode<T>>) -> Box<AVLNode<T>> {
        println!("left");

        let mut y = x.right.take().expect("AVL BROKEN");
        let mut t2 = y.left.take();

        // let mut t2 = replace(&mut y.left, t2);
        if t2.is_some() {
            let t2 = t2.as_mut().unwrap();
            let ptr = &x as *const Box<AVLNode<T>>;
            t2.parent = ptr;
            println!("{:#?} - {:#p}", t2.parent, ptr);
        }

        x.right = t2;

        y.parent = x.parent;
        println!("{:#?} - {:#?}", y.parent, x.parent);
        let ptr = &y as *const Box<AVLNode<T>>;
        x.parent = ptr;
        println!("{:#?} - {:#?} - {:p}\n", x.parent, std::ptr::addr_of!(y), y);

        self.update_height(&mut x);
        y.left = Some(x);

        self.update_height(&mut y);

        return y;
    }

    fn rebalance(&mut self, mut node: Box<AVLNode<T>>, element: &T) -> Box<AVLNode<T>> {
        self.update_height(&mut node);
        let balance = self.get_balance(&Some(&node));

        if balance == 1 && element < &node.left.as_ref().unwrap().element {
            return self.right_rotate(node);
        }

        if balance == -1 && element > &node.right.as_ref().unwrap().element {
            return self.left_rotate(node);
        }

        if balance == 1 && element > &node.left.as_ref().unwrap().element {
            node.left = Some(self.left_rotate(node.left.take().unwrap()));
            return self.right_rotate(node);
        }

        if balance == -1 && element < &node.right.as_ref().unwrap().element {
            node.right = Some(self.right_rotate(node.right.take().unwrap()));
            return self.left_rotate(node);
        }

        return node;
    }

    pub(self) fn insert_node(
        &mut self,
        node: &mut Option<Box<AVLNode<T>>>,
        element: &T,
    ) -> Box<AVLNode<T>> {
        if node.is_none() {
            self.no_nodes += 1;
            return Box::new(AVLNode::new(element.clone()));
        }

        let mut node = node.take().unwrap();

        let node = match node.element.cmp(&element) {
            cmp::Ordering::Equal => return node,
            cmp::Ordering::Less => {
                node.right = Some(self.insert_node(&mut node.right, element));
                node
            }
            cmp::Ordering::Greater => {
                node.left = Some(self.insert_node(&mut node.left, element));
                node
            }
        };

        self.rebalance(node, &element)
    }

    pub(self) fn remove_node(
        &mut self,
        node: &mut Option<Box<AVLNode<T>>>,
        element: &T,
    ) -> Option<Box<AVLNode<T>>> {
        if node.is_none() {
            return node.take();
        }

        let mut node = node.take().unwrap();

        let mut node = match node.element.cmp(&element) {
            cmp::Ordering::Less => {
                node.right = self.remove_node(&mut node.right, element);
                Some(node)
            }
            cmp::Ordering::Greater => {
                node.left = self.remove_node(&mut node.left, element);
                Some(node)
            }
            cmp::Ordering::Equal => {
                if node.left.is_none() || node.right.is_none() {
                    self.no_nodes -= 1;
                    let tmp = node;
                    if tmp.left.is_some() {
                        tmp.left
                    } else {
                        tmp.right
                    }
                    // drop(tmp);
                } else {
                    let min = self.get_minimum(node.right.as_ref().unwrap());
                    node.element = min.element.clone();
                    node.right = self.remove_node(&mut node.right, &node.element);
                    Some(node)
                }
            }
        };

        if node.is_none() {
            return node.take();
        }

        let mut node = node.unwrap();

        self.update_height(&mut node);
        let balance = self.get_balance(&Some(&node));

        let node = match balance {
            b if b == 1 && self.get_balance(&node.left.as_ref()) >= 0 => self.right_rotate(node),
            b if b == 1 && self.get_balance(&node.left.as_ref()) < 0 => {
                node.left = Some(self.left_rotate(node.left.take().unwrap()));
                self.right_rotate(node)
            }
            b if b == -1 && self.get_balance(&node.right.as_ref()) <= 0 => self.left_rotate(node),
            b if b == -1 && self.get_balance(&node.right.as_ref()) > 0 => {
                node.right = Some(self.right_rotate(node.right.take().unwrap()));
                self.left_rotate(node)
            }
            _ => node,
        };

        return Some(node);
    }
}

impl<T: Display + Ord + Debug + Clone> AVLTree<T> for MyAVLTree<T> {
    fn new() -> Self {
        Self {
            root: None,
            no_nodes: 0,
        }
    }

    fn size(&self) -> usize {
        self.no_nodes
    }

    fn height(&self) -> Option<usize> {
        if let Some(root) = &self.root {
            Some(root.node_height)
        } else {
            None
        }
    }

    fn insert(&mut self, element: T) {
        let mut root = self.root.take();
        self.root = Some(self.insert_node(&mut root, &element));
    }

    fn delete(&mut self, element: T) {
        let mut root = self.root.take();
        self.root = self.remove_node(&mut root, &element);
    }

    fn find(&self, element: T) -> bool {
        fn contains<T: Display + Ord + Debug + Clone>(
            node: &Option<Box<AVLNode<T>>>,
            element: &T,
        ) -> bool {
            if node.is_none() {
                return false;
            }
            let node = node.as_ref().unwrap();

            match node.element.cmp(&element) {
                cmp::Ordering::Equal => true,
                cmp::Ordering::Greater => contains(&node.left, element),
                cmp::Ordering::Less => contains(&node.left, element),
            }
        }

        return contains(&self.root, &element);
    }

    fn print_in_order(&self) {
        fn inorder<T: std::fmt::Display>(node: &Option<Box<AVLNode<T>>>) {
            if node.is_none() {
                return;
            }

            let node = node.as_ref().unwrap();

            inorder(&node.left);
            print!("{node} -> ");
            inorder(&node.right);
        }

        inorder(&self.root);
        println!("end");
    }

    fn print_pre_order(&self) {
        fn pre_order<T: std::fmt::Display>(node: &Option<Box<AVLNode<T>>>) {
            if node.is_none() {
                return;
            }

            let node = node.as_ref().unwrap();

            print!("{node} -> ");
            pre_order(&node.left);
            pre_order(&node.right);
        }

        pre_order(&self.root);
        println!("end");
    }

    fn clear(&mut self) {
        self.no_nodes = 0;

        fn remove<T>(node: &mut Option<Box<AVLNode<T>>>) {
            if node.is_none() {
                return;
            }

            let mut node = node.take().unwrap();

            remove(&mut node.left);
            remove(&mut node.right);

            drop(node);
        }

        remove(&mut self.root);
    }
}

pub trait AVLTree<T: std::fmt::Display + Ord> {
    fn new() -> Self;
    fn size(&self) -> usize;
    fn height(&self) -> Option<usize>;
    fn insert(&mut self, element: T);
    fn delete(&mut self, element: T);
    fn find(&self, element: T) -> bool;
    fn print_in_order(&self);
    fn print_pre_order(&self);
    fn clear(&mut self);
}
