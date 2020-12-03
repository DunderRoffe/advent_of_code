#define MAP_MAX_WIDTH 32

char test_input[][MAP_MAX_WIDTH] = {
	"..##.......",
	"#...#...#..",
	".#....#..#.",
	"..#.#...#.#",
	".#...##..#.",
	"..#.##.....",
	".#.#.#....#",
	".#........#",
	"#.##...#...",
	"#...##....#",
	".#..#...#.#"
};

char real_input[][MAP_MAX_WIDTH] = {
	"...#...#....#....##...###....#.",
	"#.#...#...#....#.........#..#..",
	".#....##..#.#..##..##..........",
	".....#.#.............#..#......",
	".......#...#.##.#......#..#.#..",
	"#.#....#......##........##.....",
	".....##.#....#..#...#...##...#.",
	"...#...#..#.......#..#...##...#",
	"..........#...........##.......",
	"..#..#..#...................#..",
	"#..#....#.....##.#.#..........#",
	".#.##.......###.....#.#...#....",
	".#..##....##....#.......#...###",
	"#.#..##...#.#..#...............",
	".........#....#.......##.#.#...",
	"...###...##....##...#..##.#..#.",
	"....#.........#..#...#.......#.",
	"....................#..#.#.#...",
	"..#....#..........#...........#",
	".#.....#..#.....##........##..#",
	"#..##..#...##............#..##.",
	".#..##....#..........#..#.##.#.",
	"..#####..#.#............##.....",
	"...###.#....##..#.#....#.....#.",
	".#.......##....#...#.#.....##..",
	"...#....#...##.#...#..#........",
	".####.....#....#.#.#...#.......",
	"...#....#.....#.......#........",
	"#..#.#.......#...#............#",
	"...#.....###.##....#.#.###.#...",
	".#.........#.......#.#....##...",
	"#.#..#...#.#...##......#..#....",
	".....#...#..#.#...#..###..#....",
	"......#.........#...###........",
	".....#..##...#..........#.....#",
	"..#..#.#.##.#...#....#....##..#",
	"##....#.##...#.##.#..##....#...",
	".....#.#.#.#..#....##.#...#.#..",
	".....##.......#........#.......",
	"...#.#.....#...#...##.#......##",
	"........#..#.#...#.#.....#.#..#",
	"#..##...#.#...##..##...#.#...##",
	".##.#.#..#...#.....#.#.##.#...#",
	".#.####.........##.........#..#",
	".##..............#....#...#...#",
	"......#...#..#...#..#..###.#...",
	".......##...#.#.#..##..#......#",
	".....#....#..##..#.........#...",
	".....#..#.#.#........#.#.####..",
	"#..#.......###....##...........",
	"#..##..........#.#......#.#....",
	".....##........#...#..##.......",
	"###...#.##.#.#.#.#.##...##.....",
	"....#...#........##.#.##..##...",
	".#..#.#.#......#.......##..#..#",
	".#...#.................#....#..",
	".##..#..........#..##.......#..",
	".#.#.#.....#..#.#.........##..#",
	"...#......##...#.......#...##..",
	"##...###....#.###.............#",
	"#.....#.#..#.#..#........#.#.#.",
	".....#.#......##..#.#.....#.##.",
	".......#...........#..#.......#",
	"..#....#.#.#......#.....#...#..",
	".....##........#..##..#..##....",
	"#.#........#...##....#.#..##...",
	"#......#......#....#..#...#.##.",
	"....#.#.......#.#.#............",
	"......####.#.##...#.#.##.....##",
	"..###.#.#..#.........#.####....",
	".#.......#..#.#....#.#..#.#.##.",
	"#....#....#............##...##.",
	"....#....#............#....#..#",
	"..#........#..#....#..#..#...#.",
	".#......##....#..........#....#",
	"#.##.....#..........#.###.#....",
	"....##...#.....#.#......#.##...",
	"#.#.....#.......###.###..#..#.#",
	"..###..##.............#.####.##",
	"#....#.....#....#..##.......#..",
	".....#....#...#.#.#.#..#...#.##",
	"...#.....#..#....###......#.#.#",
	"##.........#.#..#..#.#..#.....#",
	".#.....#.#....#.........##..#.#",
	".#.#..#.###..#..#..........#...",
	".##....#.#.#...#......##.....#.",
	"#.#....#....#...#...##...#..#..",
	"#...#........#....#....#......#",
	"#......#...#..#.#.##.....##..#.",
	"....#...#......##...#..#....#..",
	".#......##.##.......#.......#..",
	".#...#..####...........#.#.#...",
	".........#...#.#.........#.....",
	"#.##.....#.#..#.#.###...###..#.",
	"#...##.###......#.###..##.#.##.",
	"...##.#.....#....#..#......#...",
	"#....###.#..#...##.....#......#",
	"........###...#...#............",
	"........#....#...#...#....#...#",
	"#....#..#..#....#.#........#.#.",
	"##...#.....#.#..........#..#..#",
	"#.#...##.....#........#...#...#",
	"##.#.#.......#...#..#.###....#.",
	".#.......#....##..##...#.....#.",
	"#....#....#.....#.......#......",
	".##.##.##...##...#.#.#..#..#...",
	"#..#..#.##....#......##....###.",
	".......#.#.........#..##.#...##",
	".#..##...#....#.....#..........",
	"..#.#...#......#.#..#..........",
	".##....#.#.#.##.......###...#..",
	"..##.#...#.#.#.#.......#..#....",
	"#..#.......#...#........#.....#",
	".....#.......#......###..#.....",
	"...##.#.......#.....##.....##..",
	"##..#.......#.#.....#....#.....",
	"..#....#.##.##...#...#......#..",
	".#..#.###.#....###........#...#",
	"....##.##...##..#..#.#....#....",
	"..###...##.....##..............",
	"#....#...##...#....#..........#",
	".##........#......##...##...#.#",
	"..#.#.##..........#......#.....",
	"...#...#.........#.##........##",
	"..#.#..#.#..#...#....#...#.....",
	"...##...#..#.###.#..#.#...#....",
	"....###........#..#..##...#....",
	"#.#....##.......#.#........#...",
	".###...#..#.#.#.#..#...#..##.##",
	"..#.........#####.#......#..#..",
	"#.....#.....##..#....#...#...#.",
	"...#..#....##....##.....##.#...",
	".........#............#.##.....",
	"....##.#..#....#.##.......#..##",
	".###....#.#..#......#.#.......#",
	".###...###.#.........#.#..#...#",
	".....#........#..#.#..#.#..##.#",
	".###..#....##.........#..##....",
	"..#.......#..#..##...#.###.#...",
	"#.......#...........#.#...#.###",
	"#.##.##...##.#...##..#.....#...",
	"..#..#........###.#.....##.....",
	"#.....##....#...##...####..#..#",
	"....#........#...#...#.........",
	"......#.#.#.#.......#..#.....##",
	"..#..#....#.....#.#...##......#",
	"..#....#...#.###.........#.###.",
	"...#......##..#.#.....#...#....",
	"...#.......#...#...#........##.",
	"............#...#..#....#.....#",
	"....##......................#..",
	"#.#.#....#....#..........##....",
	"#.#.....#.#.##..#...#.##....##.",
	"...#...#..#...#..#.#.#.......#.",
	"#.....#..........#.........##.#",
	"#...##..#..#.#.......###....#..",
	".#...#..##....#.....##.......#.",
	"....#.##.....#.........#.#....#",
	"........#.#...####..#.......#.#",
	".####...#.#......####.....#.##.",
	"###..#....#..#.......#.#..##..#",
	"#......#.#....##..#.##.#....#.#",
	"...###...#...#..##.#..#..#.#...",
	"...##..##....#..#.....#........",
	".....#..............#......#..#",
	"......#....#......#..#.........",
	"#..#.....#.##...........##.....",
	".#..#.#..................##....",
	"#.#..#..##...#....#.#......#...",
	".##.#.##......#.##...#...#...#.",
	"..#...#.........#.#..#.#....#..",
	".#.####.#..#.#......##.#..#....",
	"#..#.......#....#..............",
	"....#............#..#..........",
	".....#####.....#.....#..##...##",
	"#.#....#.#...............#..##.",
	".#.#..#...#......#.....#.#.#...",
	".#....#.#.#......#.....##....#.",
	"....#....#.##..#.......###...##",
	".....#..#.##...#...#...#..#.#..",
	"##..#........#.#..#..##......#.",
	".#..#..##.......#..#.....#.....",
	".#.#.....###..##.#.#...........",
	"..##..##.####..........#..#....",
	"..##..#..#...#....#......#.#...",
	"#...#.#......##.....##.#..###..",
	"#..#..............#........##.#",
	".........#.##..#.#..#..##.##.#.",
	"#....##....#.#..#.#...##..#....",
	".#....#.......#............##..",
	".......#.#.......#...#.#......#",
	"......##...#.......#.#........#",
	"..###..#.#.##....##...#....##..",
	"..##.##..........##..###.......",
	".#.#.#..#..#.#.......#.#...##..",
	"..#..##.........#.###..#......#",
	"....#.#.#...##.#...#...##..###.",
	"..###..##.........##...#...#..#",
	".#..##...#.......#.......#..#.#",
	"........##....##....#.#.###.#.#",
	"#.....#.#.................#.#..",
	"....#.#.#.....##.####.#......#.",
	"....#.......#.#.##.##..........",
	"...#...........#...#.##...#.###",
	"#....#....#..........#.##......",
	"##..#...........##.....##.##...",
	".#.##...##..##....#..#.....####",
	"#...#...#.##..........##..##...",
	"....##..#....#.....#.#...#....#",
	"..#....#..##...###.#.#.........",
	"#......#.#.#...#...#.........#.",
	"#............###.#.#.#..##...#.",
	".##.....####...##..##..#..##.#.",
	"#..#........#.....#.#.....#...#",
	"#............#....#.#.#........",
	"......##...##.#....#.....#...#.",
	"..#........##......#.#.....##..",
	".#..#..#.....##.......#..#.#..#",
	".#....#..#....##.#.#.#..#..#.##",
	".####.#..........#...#..##.....",
	"...###..###...##..#............",
	"#..#.....##.#...#..##..#.......",
	".....##....#...###.##...#......",
	"...##..#...#..#..##....##....#.",
	"...###....#.###.#.#.##....#....",
	"##.#.#.....#....#.#....#..#....",
	".......##.....#.#..##...##...#.",
	".#....#.#...##.#..#....#.....#.",
	"..#...#..#...#.##........#...#.",
	"#....#......##.#....##...#.#..#",
	".....#..#..#..#......#...#.#.#.",
	"..###....#........#...#.......#",
	"###...#.......#.#.......##.##..",
	"......##.....#.#........#....#.",
	"#.##..#.#.#.#..#....#.##.....#.",
	"..........#.##.#...#...#..#..#.",
	"..#...##.#..........#..##.###..",
	"..###..##.##..#.#...##.####..#.",
	"#.#.#...............##....###.#",
	"....#.........#.#....#.#....#.#",
	"..#...#.###...#....###.....#...",
	"..#..#....#...#............#...",
	".#..#....#..##.....##..........",
	"..#....#.#...#.#.#.#.......##.#",
	".........#....##........#.#....",
	"...#..##.#..#.##...#...#.#....#",
	"....####...#...####.#....###..#",
	"......##...#.##.#.......#..#...",
	"#.#...#.#...#.#...#....#.#.#...",
	".#.....##...#.....###.#....#...",
	"......##.....###...#.#...#.#...",
	"#..#..##.#.#......#....#..#..#.",
	"....#.###.....#..#...#.##.....#",
	"##.##........#......#....#..##.",
	"##.....##.#.....#.....##.....#.",
	".....#.##...#.#..#.#.#.....#...",
	".#.##..#...#.#..#.....#.#......",
	".....##.......#..#...##..#..#..",
	"#.....#..#.####......#........#",
	".#..#..##.#..##............#..#",
	".##..#.#....##.##.....#......#.",
	".......##.........#..#.........",
	".#...#.......................#.",
	"#......#.#....##.#.......#..#..",
	"..##..##......#.......#....#.#.",
	"##......#......##...##.........",
	"..#....####....#.#.....##.#.#..",
	"..........#..#.#.#.....#..#.#..",
	"##..##...........##.......#....",
	"##....#.#....#..#......###....#",
	"...#.#.#..#.......##.......#...",
	"#....#.......#.......#.........",
	"...##......##....#...#......#.#",
	"#......#####.#.........#.....#.",
	"#..#.............#..#....#...#.",
	".......#.##..#..#..#..#....####",
	"......#.##..##..........###...#",
	".#.##....###..#........#....##.",
	"#......#..#...###.#...#.....#..",
	".#.#.......#....##.......#.#...",
	"..#.##..#..##.....#.........#.#",
	"#.#...#..#.##....#.......##....",
	".#.....###....#.#..#...#.....#.",
	"#...#..#.......#.#.....##...#.#",
	"#.#####.........#....##.....#..",
	"#....#..##...#....#.##.......#.",
	".#.#.........##....##....#.....",
	"...#..##.......#....#.#.#......",
	"#.###.##...###....#.....#.####.",
	".#...#.#.#..##.#..........#....",
	"#.#.....#.##.#..####.....##.#..",
	"...###.##..####.......#......##",
	".##..#.........#...#.#.....#.##",
	"..#.....##....###.....#.#...##.",
	"#....#....#..#....#.##.........",
	"......###....#.#..#..#....##...",
	".#.#................#.......##.",
	"...#.......#.........#.#.......",
	"...#..........#...##.....###...",
	"....#......#...#...............",
	".##...#....#.....#.##......#...",
	".#.....###...##..##...#.#......",
	"....##........#.....#...#....#.",
	"#.........#.#...##...#.#..#....",
	"...#.#.....#.#........#.#....#.",
	".#........#.....#.#.#.#.#..#...",
	"....#...#.....#.#....#........#",
	"..###.#....#.#....##...##..#.##",
	".#....#.#.####.#.#.....#.......",
	".#...#...#.................##.#",
	"..................##..#..#.#.#.",
	".#..#............##....###.....",
	".......#....#...........#......",
	"....#.#.#.....###.........#..##",
	"...#.#....#.#.##.#.##.....##..#",
	".#.##.#...##...#.......#.....##",
	".#............#...#..##...#.#.#",
	"#.##..#.##..#..##.###.#........",
	"..............##....#...#..#.#.",
	".#.#...#.#....#....###........#",
	".#....#.#....#......###........",
	"..#.......##......#.##.....#...",
	".....#......#..#...#.#.....#...",
};