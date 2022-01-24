use exercises::ex9::{Graph, MyGraph, Vertex};

#[test]
fn graph_test() {
    let mut graph = MyGraph::new();
    let vertices1 = vec![
        Vertex::new("0".to_string()),
        Vertex::new("1".to_string()),
        Vertex::new("2".to_string()),
        Vertex::new("3".to_string()),
        Vertex::new("4".to_string()),
        Vertex::new("9".to_string()),
    ];

    println!("------------------- PART 1 -------------------");

    for v in &vertices1 {
        graph.insert_vertex(v.clone());
    }

    print!("Vertices in Graph: ");
    for v in graph.get_vertices() {
        print!("{:?} ", v);
    }
    println!(
        "\nNumber of Vertices: {:?}\n",
        graph.get_number_of_vertices()
    );

    let vertices1 = vec![
        Vertex::new("0".to_string()),
        Vertex::new("1".to_string()),
        Vertex::new("2".to_string()),
        Vertex::new("3".to_string()),
        Vertex::new("4".to_string()),
        Vertex::new("9".to_string()),
    ];
    graph.insert_edge(vertices1[0].clone(), vertices1[1].clone(), 1);
    graph.insert_edge(vertices1[0].clone(), vertices1[3].clone(), 2);
    graph.insert_edge(vertices1[1].clone(), vertices1[2].clone(), 3);
    graph.insert_edge(vertices1[1].clone(), vertices1[3].clone(), 4);
    graph.insert_edge(vertices1[2].clone(), vertices1[4].clone(), 5);
    graph.insert_edge(vertices1[3].clone(), vertices1[4].clone(), 6);

    print!("Vertices in Graph after insertEdge: ");

    for v in &graph.get_vertices() {
        print!("{:?} ", v);
    }
    println!(
        "\nNumber of Vertices afer insertEdge: {:?}\n",
        graph.get_number_of_vertices()
    );

    println!("\n=========== Matrix ===========");

    let matrix = graph.get_adjacency_matrix();
    print!("    ");
    for i in 0..vertices1.len() - 1 {
        print!("{}--", vertices1[i].name);
    }
    print!("{} \n", vertices1[vertices1.len() - 1].name);

    for (i, m) in matrix.iter().enumerate() {
        print!("{}: ", vertices1[i].name);

        for n in m {
            let spacing = if (*n) < 0 { "" } else { " " };
            print!("{}{} ", spacing, n);
        }

        println!("\n");
    }

    let vertices2 = vec![
        Vertex::new("5".to_string()),
        Vertex::new("6".to_string()),
        Vertex::new("7".to_string()),
    ];

    for vertex in &vertices2 {
        graph.insert_vertex(vertex.clone());
    }

    graph.insert_edge(vertices2[0].clone(), vertices2[1].clone(), 1);
    graph.insert_edge(vertices2[0].clone(), vertices2[2].clone(), 2);

    println!("\n=========== List ===========");

    for search_vertex in &vertices1 {
        print!("{:?}: ", search_vertex);
        for v in &graph.get_adjacency_list(search_vertex) {
            print!("{} ", v.name);
        }
        print!("\n");
    }

    println!("\n------------------- PART 2 -------------------");

    println!("isCyclic: {}", graph.is_cyclic());
    println!("isConnected: {}", graph.is_connected());
    println!("Connected Components: {}", graph.get_number_of_components());

    graph.print_components();
}

#[test]
fn external_test() {
    println!("\n------------------- EXTERNAL VALUES -------------------");
    let mut graph = MyGraph::new();
    graph.insert_edge(
        Vertex::new("5".to_string()),
        Vertex::new("7".to_string()),
        1,
    );
    graph.insert_edge(
        Vertex::new("1".to_string()),
        Vertex::new("0".to_string()),
        2,
    );
    graph.insert_edge(
        Vertex::new("3".to_string()),
        Vertex::new("0".to_string()),
        3,
    );
    graph.insert_edge(
        Vertex::new("3".to_string()),
        Vertex::new("4".to_string()),
        4,
    );
    graph.insert_edge(
        Vertex::new("2".to_string()),
        Vertex::new("4".to_string()),
        5,
    );
    graph.insert_edge(
        Vertex::new("1".to_string()),
        Vertex::new("4".to_string()),
        6,
    );
    graph.insert_edge(
        Vertex::new("1".to_string()),
        Vertex::new("2".to_string()),
        6,
    );
    graph.insert_edge(
        Vertex::new("1".to_string()),
        Vertex::new("3".to_string()),
        6,
    );

    // println!("isCyclic: {}", graph.is_cyclic()); // matches
    assert_eq!(false, graph.is_cyclic());

    let mut graph2 = MyGraph::new();
    graph2.insert_edge(
        Vertex::new("5".to_string()),
        Vertex::new("8".to_string()),
        1,
    );
    graph2.insert_edge(
        Vertex::new("1".to_string()),
        Vertex::new("0".to_string()),
        2,
    );
    graph2.insert_edge(
        Vertex::new("3".to_string()),
        Vertex::new("1".to_string()),
        3,
    );
    graph2.insert_edge(
        Vertex::new("3".to_string()),
        Vertex::new("0".to_string()),
        4,
    );
    graph2.insert_edge(
        Vertex::new("3".to_string()),
        Vertex::new("4".to_string()),
        5,
    );
    graph2.insert_edge(
        Vertex::new("2".to_string()),
        Vertex::new("4".to_string()),
        6,
    );
    graph2.insert_edge(
        Vertex::new("1".to_string()),
        Vertex::new("4".to_string()),
        6,
    );
    graph2.insert_edge(
        Vertex::new("1".to_string()),
        Vertex::new("2".to_string()),
        6,
    );
    graph2.insert_edge(
        Vertex::new("1".to_string()),
        Vertex::new("3".to_string()),
        6,
    );

    // println!("isCyclic: {}", graph2.is_cyclic()); // matches
    assert_eq!(true, graph2.is_cyclic());

    let mut g = MyGraph::new();
    g.insert_edge(
        Vertex::new("0".to_string()),
        Vertex::new("1".to_string()),
        1,
    );
    g.insert_edge(
        Vertex::new("0".to_string()),
        Vertex::new("2".to_string()),
        1,
    );
    g.insert_edge(
        Vertex::new("1".to_string()),
        Vertex::new("2".to_string()),
        1,
    );
    g.insert_edge(
        Vertex::new("2".to_string()),
        Vertex::new("0".to_string()),
        1,
    );
    g.insert_edge(
        Vertex::new("2".to_string()),
        Vertex::new("3".to_string()),
        1,
    );
    g.insert_edge(
        Vertex::new("3".to_string()),
        Vertex::new("3".to_string()),
        1,
    );

    // println!("isCyclic: {}", g.is_cyclic()); // matches
    assert_eq!(true, g.is_cyclic());
}
