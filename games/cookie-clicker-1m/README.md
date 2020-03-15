# Cookie Clicker 1M

Current status: **implemented for Windows**

## Description (How to play)
**Goal:** obtain `1'000'000` cookies as fast as possible.

1. Your cookie company has two main attributes: `production rate` and `capacity`.
- `production rate` - number of cookies your factory produces in second (measured in `c/s` (cookies per second))
- `capacity` - maximum number of cookies your can obtain at a time in your storage (measured in `c` (cookies))

You start with `production rate` of `1 c/s` and `capacity` of `10 c`.

2. You can buy upgrades for your company:
- Factory upgrades (each can be bought multiple times):

| Upgrade name |   Cost  | Production rate |
|:------------:|:-------:|:---------------:|
| Worker       |  `10 c` |  `1 c/s`        |
| Specialist   | `250 c` |  `10 c/s`       |
| Professional | `10000 c` |  `500 c/s`    |
| Machine      | `200000 c` |  `10000 c/s` |

**Note**: Price of each factory upgrades raises up by `10%` after each purchase of that upgrade.
If the price becomes not integer after this transformation then it is rounded down.

- Storage upgrades (each can be bought only once):

| Upgrade name |   Cost  | Capacity |
|:------------:|:-------:|:--------:|
| Upgrade 1    |  `10 c` |  `25 c`  |
| Upgrade 2    |  `20 c` |  `50 c`  |
| Upgrade 3    | `45 c`  | `100 c`  |
| Upgrade 4    | `99 c`  | `250 c`  |
| Upgrade 5    | `200 c` | `500 c`  |
| Upgrade 6    | `499 c` | `777 c`  |
| Upgrade 7    | `667 c` | `1000 c` |
| Upgrade 8    | `900 c` | `2000 c` |
| Upgrade 9    | `1750 c` | `3000 c` |
| Upgrade 10   | `2250 c` | `5000 c` |
| Upgrade 11   | `3750 c` | `7500 c` |
| Upgrade 12   | `6650 c` | `10000 c` |
| Upgrade 13   | `9001 c` | `15000 c` |
| Upgrade 14   | `14444 c` | `25000 c` |
| Upgrade 15   | `20000 c` | `50000 c` |
| Upgrade 16   | `49999 c` | `100000 c` |
| Upgrade 17   | `98000 c` | `250000 c` |
| Upgrade 18   | `200000 c` | `350000 c` |
| Upgrade 19   | `300000 c` | `500000 c` |
| Upgrade 20   | `450000 c` | `750000 c` |
| Upgrade 21   | `600000 c` | `900000 c` |
| Upgrade 22   | `800000 c` | `1000000 c` |

**Note:** you can buy storage upgrades only in consecutive order. E.g.: you cannot buy "Upgrade 5" without buying "Upgrade 4" or "Upgrade 3". This is done not only by upgrades prices policy but also by the whole game concept design (this means that even if prices were another this should be principle must remain).

3. As soon as you obtain `1000000 c` you will get score of `60000 / <time of playing in seconds>`. 

**Note:** `<time of playing in seconds>` is equal to `<time of playing in millseconds> / 1000` where `<time of playing in milliseconds>` is rounded down. E.g.: If you won the game in `3219.561 milliseconds` then `<time of playing in seconds> = 3.219`.

## Compilation
```
make
```

## Clean-up
```
make clean
```

## Requirements
You need `make` and `g++` to compile this game.
