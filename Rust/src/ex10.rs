use std::collections::{BTreeSet, BinaryHeap};

use super::ex9::{Graph, MyGraph, Vertex};

pub trait Dijkstra {
    fn shortest_path_dijkstra(&self, source: &Vertex);
}

impl Dijkstra for MyGraph {
    #[allow(non_snake_case)]
    fn shortest_path_dijkstra(&self, source: &Vertex) {
        let vertices: &Vec<Vertex> = self.vertices.as_ref();

        let mut S = BTreeSet::new();
        let mut P = vertices.clone();

        let mut D = vec![i64::MAX; vertices.len()];
        let idx = vertices
            .iter()
            .position(|v| v == source)
            .expect("Source doesn't exist in the graph");
        D[idx] = 0;

        let mut Q = BinaryHeap::new();
        Q.push(PQElement::new(source.clone(), 0));

        while let Some(PQElement { vertex: u, .. }) = Q.pop() {
            S.insert(u.clone());
            let idx_u = vertices.iter().position(|v| (*v) == u).unwrap();

            for v in &self.get_adjacency_list(&u) {
                let idx_v = vertices.iter().position(|v1| v1 == v).unwrap();
                let distance = D[idx_u] + self.get_edge_weight(&u, v);

                if D[idx_v] > distance {
                    D[idx_v] = distance;
                    Q.push(PQElement::new(v.clone(), distance));
                    P[idx_v] = u.clone();
                }
            }
        }

        println!("\nDistances to Source: ");
        for (i, v) in S.iter().rev().enumerate() {
            println!("{:?}: {:?}", v, D[i]);
        }
    }
}

#[derive(Debug, Clone, Eq)]
struct PQElement {
    vertex: Vertex,
    priority: i64,
}

impl PQElement {
    fn new(vertex: Vertex, priority: i64) -> PQElement {
        PQElement { vertex, priority }
    }
}

impl PartialEq for PQElement {
    fn eq(&self, other: &Self) -> bool {
        self.vertex == other.vertex && self.priority == other.priority
    }
}

impl Ord for PQElement {
    fn cmp(&self, other: &Self) -> std::cmp::Ordering {
        other
            .priority
            .cmp(&self.priority)
            .then_with(|| self.vertex.cmp(&other.vertex))
    }
}

impl PartialOrd for PQElement {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        Some(self.cmp(other))
    }
}
