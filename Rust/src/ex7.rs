use std::fmt::Display;

#[derive(Debug, PartialEq, Eq, Clone)]
pub struct OrderedNode {
    element: i32,
    is_deleted: bool,
}

impl OrderedNode {
    fn new(key: Option<i32>, is_deleted: Option<bool>) -> OrderedNode {
        let element = key.unwrap_or(i32::MAX);
        let is_deleted = is_deleted.unwrap_or(true);

        OrderedNode {
            element,
            is_deleted,
        }
    }
}

#[derive(Debug, Clone, PartialEq, Eq)]
pub struct MyOrderedDoubleHashSet {
    hash_table: Vec<Box<OrderedNode>>,
    capacity: usize,
    nr_elements: usize,
}

impl MyOrderedDoubleHashSet {
    fn h1(&self, key: i32) -> usize {
        key as usize % self.capacity
    }

    fn h2(&self, key: i32) -> usize {
        1 + (key as usize % (self.capacity - 2))
    }

    pub(self) fn swap(a: &mut i32, b: &mut i32) {
        if *a == *b {
            return;
        }
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
    }

    fn calc_index(&self, h1: usize, h2: usize) -> usize {
        let s = h1 as isize - h2 as isize;
        let calc = s % self.capacity as isize;
        calc.abs().try_into().unwrap_or(0)
    }
}

impl OrderedDoubleHashSet for MyOrderedDoubleHashSet {
    fn new(capacity: usize) -> Self {
        let mut hash_table = Vec::with_capacity(capacity);

        for _ in 0..capacity {
            hash_table.push(Box::new(OrderedNode::new(None, None)));
        }

        MyOrderedDoubleHashSet {
            hash_table,
            capacity,
            nr_elements: 0,
        }
    }

    fn size(&self) -> usize {
        self.nr_elements
    }

    fn insert(&mut self, mut key: i32) -> bool {
        if self.contains(key) || self.nr_elements == self.capacity {
            return false;
        }

        self.nr_elements += 1;

        let hash_1 = self.h1(key);

        {
            let mut current = self.hash_table[hash_1].as_mut();

            if current.is_deleted && key <= current.element {
                current.is_deleted = false;
                current.element = key;
                return true;
            }
        }

        let mut index = hash_1;

        for _ in 0..self.capacity {
            if key < self.hash_table[hash_1].element {
                let curr = &mut self.hash_table[hash_1].element;
                MyOrderedDoubleHashSet::swap(&mut key, curr);
            }

            let hash_2 = self.h2(key);
            index = self.calc_index(index, hash_2);

            if self.hash_table[index].is_deleted {
                self.hash_table[index].element = key;
                self.hash_table[index].is_deleted = false;
                return true;
            }
        }

        return false;
    }

    fn remove(&mut self, key: i32) -> bool {
        if !self.contains(key) {
            return false;
        }

        self.nr_elements -= 1;

        let hash_1 = self.h1(key);

        {
            let mut current = self.hash_table[hash_1].as_mut();

            if current.is_deleted && key == current.element {
                current.is_deleted = false;
                return true;
            }
        }

        let mut index = hash_1;
        let hash_2 = self.h2(key);

        for _ in 0..self.capacity {
            index = self.calc_index(index, hash_2);

            if !self.hash_table[index].is_deleted && key == self.hash_table[index].element {
                self.hash_table[index].is_deleted = true;
                return true;
            }
        }

        return false;
    }

    fn contains(&self, key: i32) -> bool {
        let hash_1 = self.h1(key);

        let current = &self.hash_table[hash_1];
        if key <= current.element && current.is_deleted {
            return false;
        }

        if key == current.element && !current.is_deleted {
            return true;
        }

        let mut index = hash_1;
        let hash_2 = self.h2(key);

        for _ in 0..self.capacity {
            index = self.calc_index(index, hash_2);

            if !self.hash_table[index].is_deleted && key == self.hash_table[index].element {
                return true;
            }
        }

        return false;
    }

    fn clear(&mut self) {
        if self.nr_elements == 0 {
            return;
        }
        self.nr_elements = 0;

        for i in 0..self.capacity {
            drop(&self.hash_table[i]);
            self.hash_table[i] = Box::new(OrderedNode::new(None, None));
        }
    }
}

impl Display for MyOrderedDoubleHashSet {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        for (i, current) in self.hash_table.iter().enumerate() {
            if current.is_deleted {
                continue;
            }

            let el = current.element;
            write!(f, "Element: {el}, Index: {i} -> ")?;
        }

        write!(f, "end")
    }
}

impl Drop for MyOrderedDoubleHashSet {
    fn drop(&mut self) {
        for node in &self.hash_table {
            drop(node);
        }
    }
}

pub trait OrderedDoubleHashSet {
    fn new(capacity: usize) -> Self;
    fn size(&self) -> usize;
    fn insert(&mut self, key: i32) -> bool;
    fn remove(&mut self, key: i32) -> bool;
    fn contains(&self, key: i32) -> bool;
    fn clear(&mut self);
}

type Link = Option<Box<ChainingNode>>;

#[derive(Debug, PartialEq, Eq, Clone)]
pub struct ChainingNode {
    element: i32,
    next: Link,
}

impl ChainingNode {
    fn new(element: Option<i32>, node: Link) -> ChainingNode {
        let element = element.unwrap_or(0);

        ChainingNode {
            element,
            next: node,
        }
    }
}

#[derive(Debug, PartialEq, Eq, Clone)]
pub struct MyChainingHashset {
    hash_table: Vec<Link>,
    nr_elements: usize,
    capacity: usize,
}

impl MyChainingHashset {
    fn hash_code(&self, key: i32) -> usize {
        key as usize % self.capacity
    }
}

impl ChainingHashset for MyChainingHashset {
    fn new(capacity: usize) -> Self {
        let mut hash_table = Vec::with_capacity(capacity);

        for _ in 0..capacity {
            hash_table.push(None);
        }

        MyChainingHashset {
            hash_table,
            capacity,
            nr_elements: 0,
        }
    }

    fn size(&self) -> usize {
        self.nr_elements
    }

    fn insert(&mut self, key: i32) -> bool {
        if self.contains(key) {
            return false;
        };

        let hash = self.hash_code(key);
        self.hash_table[hash] = {
            let next = self.hash_table[hash].take();
            let new_node = Box::new(ChainingNode::new(Some(key), next));
            Some(new_node)
        };

        self.nr_elements += 1;

        return true;
    }

    fn remove(&mut self, key: i32) -> bool {
        if !self.contains(key) {
            return false;
        };

        let hash = self.hash_code(key);

        if let Some(current) = self.hash_table[hash].as_mut() {
            if current.element == key {
                self.nr_elements -= 1;
                let next = current.next.take();

                drop(current);

                self.hash_table[hash] = next;

                return true;
            }
        }

        let mut current = self.hash_table[hash].as_mut();

        while let Some(curr) = current {
            if let Some(node) = curr.next.as_mut() {
                if node.element == key {
                    self.nr_elements -= 1;
                    let next = node.next.take();

                    drop(curr.next.as_ref());

                    curr.next = next;

                    return true;
                }
            }
            current = curr.next.as_mut();
        }

        return false;
    }

    fn contains(&self, key: i32) -> bool {
        let hash = self.hash_code(key);

        let mut current = self.hash_table[hash].as_ref();
        while let Some(node) = current {
            if node.element == key {
                return true;
            }

            current = node.next.as_ref();
        }

        return false;
    }

    fn clear(&mut self) {
        if self.nr_elements == 0 {
            return;
        }

        self.nr_elements = 0;
        for i in 0..self.capacity {
            let mut current = self.hash_table[i].take();

            while let Some(node) = current.as_mut() {
                let next = node.next.take();

                drop(node);

                current = next;
            }
        }
    }
}

impl Display for MyChainingHashset {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        for (i, mut node) in self.hash_table.iter().enumerate() {
            write!(f, "{i}: ")?;
            while let Some(current) = node {
                let el = current.element;
                write!(f, "{el} -> ")?;
                node = &current.next;
            }
            write!(f, "\n")?;
        }

        Ok(())
    }
}

impl Drop for MyChainingHashset {
    fn drop(&mut self) {
        self.clear();
    }
}

pub trait ChainingHashset {
    fn new(capacity: usize) -> Self;
    fn size(&self) -> usize;
    fn insert(&mut self, key: i32) -> bool;
    fn remove(&mut self, key: i32) -> bool;
    fn contains(&self, key: i32) -> bool;
    fn clear(&mut self);
}
