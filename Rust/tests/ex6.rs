use exercises::ex6::{AVLNode, AVLTree, MyAVLTree};

#[test]
fn avt_test() {
    let mut tree = MyAVLTree::new();

    // for i in [44, 62, 17, 32, 50, 78, 54, 48, 88] {
    //     tree.insert(i);
    // }

    for i in [1, 2, 3, 4, 5, 6, 7, 8] {
        tree.insert(i);
    }

    let s = tree.root.as_ref().unwrap();
    // println!("{:#?}", s as *const Box<AVLNode<i32>>);
    // println!("{:p}", s);
    println!("{:#?}", std::ptr::addr_of!(s));

    let s = tree.root.as_ref().unwrap().left.as_ref().unwrap();
    println!("{:p}", s);
    println!("{:#?}", std::ptr::addr_of!(s));

    println!("{tree:#?}");

    // println!("Size: {}", tree.size());
    // println!("Height: {:?}", tree.height());
    // tree.print_in_order();

    // tree.delete(7);

    // // println!("{tree:#?}");

    // println!("Size: {}", tree.size());
    // println!("Height: {:?}", tree.height());
    // tree.print_in_order();
    // tree.print_pre_order();
}
