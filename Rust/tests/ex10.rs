use exercises::ex10::Dijkstra;
use exercises::ex9::{Graph, MyGraph, Vertex};

#[test]
fn dijkstra_test() {
    let mut graph = MyGraph::new();

    let vertices1 = vec![
        Vertex::new("0".to_string()),
        Vertex::new("1".to_string()),
        Vertex::new("2".to_string()),
        Vertex::new("3".to_string()),
        Vertex::new("4".to_string()),
    ];

    graph.insert_edge(vertices1[0].clone(), vertices1[1].clone(), 10);
    graph.insert_edge(vertices1[0].clone(), vertices1[3].clone(), 5);
    graph.insert_edge(vertices1[1].clone(), vertices1[2].clone(), 1);
    graph.insert_edge(vertices1[1].clone(), vertices1[3].clone(), 2);
    graph.insert_edge(vertices1[2].clone(), vertices1[4].clone(), 4);
    graph.insert_edge(vertices1[3].clone(), vertices1[4].clone(), 2);

    graph.shortest_path_dijkstra(&vertices1[0]);
}
