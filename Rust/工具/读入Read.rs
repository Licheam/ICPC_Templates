#[allow(unused_macros)]
macro_rules! scanln {
    ($($i:expr), +) => {
        let mut buf = String::new();
        std::io::stdin().read_line(&mut buf).unwrap();
        let mut iter = buf.split_whitespace();
        $(
            loop {
                if let Some(val) = iter.next() {
                    $i = val.parse().unwrap();
                    break;
                }
                buf = String::new();
                std::io::stdin().read_line(&mut buf).unwrap();
                iter = buf.split_whitespace();
            }
        )*
    };

    ($vec:expr ; $n:expr) => {
        let mut buf = String::new();
        std::io::stdin().read_line(&mut buf).unwrap();
        $vec = std::iter::once(Default::default())
            .chain(buf
            .split_whitespace()
            .map(|x| x.parse().unwrap()).take($n))
            .collect();
    };

    ($vec:expr ;) => {
        let mut buf = String::new();
        std::io::stdin().read_line(&mut buf).unwrap();
        $vec = std::iter::once(Default::default())
            .chain(buf
            .split_whitespace()
            .map(|x| x.parse().unwrap()))
            .collect();
    };
}

fn solve() {
}

fn main() {
    #[allow(unused_mut, unused_assignments)]
    let mut t: usize = 1;
    // scanln!(t);
    for _cas in 1..=t {
        // print!("Case #{}: ", _cas);
        solve();
    }
}