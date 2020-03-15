# Cookie Clicker 1M

Current status: **concept design**

## Description (How to play)
**Goal:** obtain `1'000'000` cookies as fast as possible.

1. Your cookie company has two main attributes: `production rate` and `capacity`.
- `production rate` - number of cookies your factory produces in second (measured in c/s (cookies per second))
- `capacity` - maximum number of cookies your can obtain at a time in your storage (measured in c (cookies))

You start with `production rate` of `1 c/s` and `capacity` of `10 c`.

2. You can buy upgrades for your company:
- Factory upgrades (each can be bought multiple times):
- Storage upgrades (each can be bought only once):
  - Upgrade 1. Cost: `10 c`. Maximum capacity: `25 c`.
  - Upgrade 2. Cost: `20 c`. Maximum capacity: `50 c`.
  - Upgrade 3. Cost: `45 c`. Maximum capacity: `100 c`.
  - Upgrade 4. Cost: `99 c`. Maximum capacity: `250 c`.
  - Upgrade 5. Cost: `200 c`. Maximum capacity: `500 c`.
  - Upgrade 6. Cost: `499 c`. Maximum capacity: `777 c`.
  - Upgrade 7. Cost: `666 c`. Maximum capacity: `1000 c`.
  - Upgrade 8. Cost: `900 c`. Maximum capacity: `2000 c`.
  - Upgrade 9. Cost: `1750 c`. Maximum capacity: `3000 c`.
  - Upgrade 10. Cost: `2250 c`. Maximum capacity: `5000 c`.
  - Upgrade 11. Cost: `3750 c`. Maximum capacity: `7500 c`.
  - Upgrade 12. Cost: `6650 c`. Maximum capacity: `10000 c`.
  - Upgrade 13. Cost: `9001 c`. Maximum capacity: `15000 c`.
  - Upgrade 14. Cost: `14444 c`. Maximum capacity: `25000 c`.
  - Upgrade 15. Cost: `20000 c`. Maximum capacity: `50000 c`.
  - Upgrade 16. Cost: `49999 c`. Maximum capacity: `100000 c`.

**Note:** you can buy storage upgrades only in consecutive order. E.g. you cannot buy "Upgrade 5" without buying "Upgrade 4" or "Upgrade 3". This is done not only by upgrades prices policy but also by the whole game concept design.

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
