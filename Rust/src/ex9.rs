use std::{
    cmp::PartialEq,
    io::{self, Write},
};

#[derive(Debug, Clone)]
pub struct Vertex {
    pub name: String,
}

impl Vertex {
    pub fn new(name: String) -> Vertex {
        Vertex { name }
    }
}

impl PartialEq for Vertex {
    fn eq(&self, other: &Self) -> bool {
        self.name == other.name
    }
}

#[derive(Debug, Clone, Copy, PartialEq)]
enum Color {
    WHITE,
    GRAY,
    BLACK,
}

#[derive(Debug)]
struct Edge {
    incoming: Vertex,
    out: Vertex,
    weight: u32,
}

impl Edge {
    pub fn new(incoming: Vertex, out: Vertex, weight: u32) -> Edge {
        Edge {
            incoming,
            out,
            weight,
        }
    }
}

pub struct MyGraph {
    edges: Vec<Edge>,
    vertices: Vec<Vertex>,
}

impl PartialEq for Edge {
    fn eq(&self, other: &Self) -> bool {
        self.incoming == other.incoming && self.out == other.out
    }
}

impl MyGraph {
    pub fn new() -> MyGraph {
        MyGraph {
            edges: vec![],
            vertices: vec![],
        }
    }
}

impl MyGraph {
    fn color_of_vertex(&self, v: &Vertex, colors: &Vec<Color>) -> Color {
        let idx = self.vertices.iter().position(|other| other == v);

        match idx {
            Some(idx) => colors[idx],
            None => Color::WHITE,
        }
    }

    fn index_of_vertex(&self, v: &Vertex) -> usize {
        self.vertices.iter().position(|other| other == v).unwrap()
    }

    fn dfs_visit(
        &self,
        v: &Vertex,
        colors: &mut Vec<Color>,
        count: &mut usize,
        is_cyclic: &mut bool,
    ) {
        colors[self.index_of_vertex(v)] = Color::GRAY;

        for adj_vertex in &self.get_adjacency_list(v) {
            let color = self.color_of_vertex(adj_vertex, colors);

            match color {
                Color::WHITE => {
                    (*count) += 1;
                    self.dfs_visit(adj_vertex, colors, count, is_cyclic)
                }
                Color::GRAY => *is_cyclic = true,
                Color::BLACK => continue,
            }
        }

        colors[self.index_of_vertex(v)] = Color::BLACK
    }
}

impl Graph for MyGraph {
    fn insert_vertex(&mut self, v: Vertex) -> isize {
        if self.vertices.contains(&v) {
            return -1;
        };
        self.vertices.push(v);

        return (self.vertices.len() - 1).try_into().unwrap();
    }

    fn insert_edge(&mut self, incoming: Vertex, out: Vertex, weight: u32) -> bool {
        self.insert_vertex(Vertex::new(incoming.name.clone()));
        self.insert_vertex(Vertex::new(out.name.clone()));

        let edge = Edge::new(incoming, out, weight);

        if self.edges.contains(&edge) {
            return false;
        }

        self.edges.push(edge);

        return true;
    }

    fn get_number_of_vertices(&self) -> usize {
        return self.vertices.len();
    }

    fn get_vertices(&self) -> Vec<Vertex> {
        self.vertices.clone()
    }

    fn get_edge_weight(&self, incoming: &Vertex, out: &Vertex) -> i64 {
        let edge = self
            .edges
            .iter()
            .find(|e| e.incoming == (*incoming) && e.out == (*out));

        match edge {
            Some(edge) => edge.weight.try_into().unwrap(),
            None => -1,
        }
    }

    fn get_adjacency_matrix(&self) -> Vec<Vec<i64>> {
        let size = self.vertices.len();
        let mut matrix: Vec<Vec<i64>> = vec![vec![-1; size]; size];

        for (i, v1) in self.vertices.iter().enumerate() {
            for (j, v2) in self.vertices.iter().enumerate() {
                matrix[i][j] = self.get_edge_weight(v1, v2);
            }
        }

        matrix
    }

    fn get_adjacency_list(&self, incoming: &Vertex) -> Vec<Vertex> {
        self.vertices
            .iter()
            .filter(|out| self.get_edge_weight(incoming, out) != -1)
            .map(|v| v.clone())
            .collect()
    }

    fn is_connected(&self) -> bool {
        let mut colors = vec![Color::WHITE; self.vertices.len()];

        let mut count = 0;
        let mut is_cyclic = false;

        for v in &self.vertices {
            if self.color_of_vertex(v, &colors) != Color::WHITE {
                continue;
            }

            self.dfs_visit(v, &mut colors, &mut count, &mut is_cyclic);

            if self.vertices.len() < count {
                return false;
            }
        }

        true
    }

    fn is_cyclic(&self) -> bool {
        let mut colors = vec![Color::WHITE; self.vertices.len()];

        let mut count = 0;
        let mut is_cyclic = false;

        for v in &self.vertices {
            if self.color_of_vertex(v, &colors) != Color::WHITE {
                continue;
            }

            self.dfs_visit(v, &mut colors, &mut count, &mut is_cyclic);

            if is_cyclic {
                return true;
            }
        }

        false
    }

    fn get_number_of_components(&self) -> usize {
        let mut colors = vec![Color::WHITE; self.vertices.len()];

        let mut count = 0;
        let mut is_cyclic = false;

        for v in &self.vertices {
            if self.color_of_vertex(v, &colors) != Color::WHITE {
                continue;
            }

            self.dfs_visit(v, &mut colors, &mut count, &mut is_cyclic);
            count += 1;
        }

        count
    }

    fn print_components(&self) {
        let mut colors = vec![Color::WHITE; self.vertices.len()];

        let mut count = 0;
        let mut is_cyclic = false;

        for v in &self.vertices {
            if self.color_of_vertex(v, &colors) != Color::WHITE {
                continue;
            }

            let idx = count;

            self.dfs_visit(v, &mut colors, &mut count, &mut is_cyclic);

            print!("Component: ");
            for i in idx..=count {
                print!("{:?} ", self.vertices[i]);
            }
            print!("\n");

            count += 1;
        }

        io::stdout().flush().unwrap();
    }
}

pub trait Graph {
    fn insert_vertex(&mut self, v: Vertex) -> isize;
    fn insert_edge(&mut self, incoming: Vertex, out: Vertex, weight: u32) -> bool;
    fn is_connected(&self) -> bool;
    fn is_cyclic(&self) -> bool;
    fn get_number_of_vertices(&self) -> usize;
    fn get_vertices(&self) -> Vec<Vertex>;
    fn get_edge_weight(&self, incoming: &Vertex, out: &Vertex) -> i64;
    fn get_adjacency_matrix(&self) -> Vec<Vec<i64>>;
    fn get_adjacency_list(&self, incoming: &Vertex) -> Vec<Vertex>;
    fn get_number_of_components(&self) -> usize;
    fn print_components(&self);
}
