use std::mem;

pub trait List {
    fn new() -> Self;

    /// return size of the list
    fn size(&self) -> i32;

    /**
     * returns the first element in the list
     *
     * @return element, -1 if empty
     */
    fn get_first(&self) -> i32;

    /// returns the last element in the list
    /// ## Return
    /// element, -1 if empty
    fn get_last(&self) -> i32;

    /// adds an element at the beginning of the list
    /// ## Arguments
    /// * `data` - The Nodes value(element)
    fn add_first(&mut self, data: i32);

    /**
     * adds an element at the end of the list
     *
     * @param data - The Nodes value(element)
     */
    fn add_last(&mut self, data: i32);

    /**
     * removes  the  first  element
     *
     * @return value of the removed element, -1 if empty
     */
    fn remove_first(&mut self) -> i32;

    /**
     * removes the  last  element
     *
     * @return value of the removed element, -1 if empty
     */
    fn remove_last(&mut self) -> i32;

    /// returns  element  at  position  index
    ///
    /// ## Arguments
    /// * `index` - 0 or bigger
    ///
    /// ## Return
    /// element  value, -1  if  index  is  out  of  bounds
    fn get_at(&self, index: i32) -> i32;

    /**
     * remove  element  at  position  index
     * @param index - 0 or bigger
     * @return  element  value, -1  if  index  is  out  of  bounds
     */
    fn remove_at(&mut self, index: i32) -> i32;

    /**
     * Checks if the list contains a certain value
     *
     * @param value
     * @return true if value in the list, else false
     */
    fn contains(&self, value: i32) -> bool;

    /**
     * adds an element in a sorted list
     * @param val
     */
    fn add_sorted(&mut self, val: i32);

    /**
     * sorts the list in ascending order: 1, 2, 3
     */
    fn sort_asc(&mut self);

    /**
     * sorts the list in descending order: 3, 2, 1
     */
    fn sort_des(&mut self);

    /**
     * removes  and  deletes  all  elements  of  the  list
     */
    fn clear(&mut self);

    /**
     * prints  the  list
     */
    fn print_elements(&self);
}

pub enum Link {
    Nil,
    Elem(Box<ListNode>),
}

pub struct ListNode {
    elem: i32,
    next: Link,
}

impl ListNode {
    pub fn new(data: Option<i32>, node: Option<Link>) -> Self {
        ListNode {
            elem: data.unwrap_or(0),
            next: node.unwrap_or(Link::Nil),
        }
    }
}

impl Drop for ListNode {
    fn drop(&mut self) {
        println!("Dropping Node: {}", self.elem);
    }
}

pub struct LinkedList {
    head: Link,
    tail: Link,
    list_size: i32,
}

impl List for LinkedList {
    fn new() -> Self {
        LinkedList {
            head: Link::Nil,
            tail: Link::Nil,
            list_size: 0,
        }
    }

    fn size(&self) -> i32 {
        return self.list_size;
    }

    fn get_first(&self) -> i32 {
        return match &self.head {
            Link::Elem(node) => node.elem,
            Link::Nil => -1,
        };
    }

    fn get_last(&self) -> i32 {
        return match &self.tail {
            Link::Elem(node) => node.elem,
            Link::Nil => -1,
        };
    }

    fn add_first(&mut self, elem: i32) {
        let new_node = Box::new(ListNode {
            elem: elem,
            next: mem::replace(&mut self.head, Link::Nil),
        });

        self.head = Link::Elem(new_node);
        self.list_size += 1;
    }

    fn add_last(&mut self, elem: i32) {
        let new_node = Box::new(ListNode {
            elem: elem,
            next: mem::replace(&mut self.tail, Link::Nil),
        });
        // let new_node = Box::new(ListNode::new(
        //     Some(elem),
        //     Some(mem::replace(&mut self.tail, Link::Nil)),
        // ));
        self.tail = Link::Elem(new_node);
        self.list_size += 1;
    }

    fn remove_first(&mut self) -> i32 {
        if self.list_size >= 0 {
            self.list_size -= 1;
        }

        return -1;
        // let next = match self.head {
        //     Link::Elem(node) => node.next,
        //     Link::Nil => Link::Nil,
        // };

        // let old_head = mem::replace(&mut self.head, next);

        // return match old_head {
        //     Link::Elem(node) => node.elem,
        //     Link::Nil => -1,
        // };
    }

    fn remove_last(&mut self) -> i32 {
        if self.list_size >= 0 {
            self.list_size -= 1;
        }

        return -1;
    }

    fn get_at(&self, index: i32) -> i32 {
        return -1;
    }

    fn remove_at(&mut self, index: i32) -> i32 {
        return -1;
    }

    fn contains(&self, value: i32) -> bool {
        return false;
    }

    fn add_sorted(&mut self, val: i32) {}

    fn sort_asc(&mut self) {}

    fn sort_des(&mut self) {}

    fn print_elements(&self) {
        if matches!(self.head, Link::Nil) {
            println!("The list is empty")
        }
        // while(self.) {

        // }
    }

    // pub fn pop(&mut self) -> Option<i32> {
    //     match mem::replace(&mut self.head, Link::Nil) {
    //         Link::Nil => None,
    //         Link::Elem(node) => {
    //             self.head = node.next;
    //             Some(node.elem)
    //         }
    //     }
    // }

    fn clear(&mut self) {
        let mut cur_link = mem::replace(&mut self.head, Link::Nil);
        while let Link::Elem(mut boxed_node) = cur_link {
            cur_link = mem::replace(&mut boxed_node.next, Link::Nil);
        }

        self.tail = Link::Nil;
    }
}

impl Drop for LinkedList {
    fn drop(&mut self) {
        self.clear()
    }
}
