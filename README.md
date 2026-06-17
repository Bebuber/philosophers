# philosophers

> The classic Dining Philosophers problem — concurrency, mutexes, and the art of not dying.

![Language](https://img.shields.io/badge/language-C-blue.svg)
![School](https://img.shields.io/badge/school-42%20Heilbronn-black.svg)
![Threads](https://img.shields.io/badge/concurrency-pthreads-purple.svg)
![Norm](https://img.shields.io/badge/norminette-passing-brightgreen.svg)

---

## About

**philosophers** is the 42 concurrency project based on Edsger Dijkstra's classic Dining Philosophers problem. N philosophers sit around a table, alternating between **thinking**, **eating**, and **sleeping**. There is one fork between each pair of adjacent philosophers. Each philosopher needs two forks to eat.

The challenge: prevent **deadlock** and **starvation** while keeping all philosophers alive.

---

## Rules

- Each philosopher is a **thread**.
- Each fork is a **mutex**.
- A philosopher who has not eaten within `time_to_die` milliseconds dies.
- The simulation ends when a philosopher dies — or, if `number_of_times_each_philosopher_must_eat` is set, when all philosophers have eaten enough.
- Philosophers do not communicate with each other.
- No global variables.

---

## Usage

### Build

```bash
make
```

### Run

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

| Argument | Description |
|---|---|
| `number_of_philosophers` | Number of philosophers (and forks) |
| `time_to_die` | Time (ms) a philosopher can go without eating before dying |
| `time_to_eat` | Time (ms) a philosopher takes to eat |
| `time_to_sleep` | Time (ms) a philosopher spends sleeping |
| `[number_of_times_each_philosopher_must_eat]` | *(optional)* Simulation ends when all have eaten this many times |

### Examples

```bash
# 5 philosophers, none should die
./philo 5 800 200 200

# 4 philosophers, limited meals
./philo 4 410 200 200 5

# 1 philosopher — will always die (only 1 fork)
./philo 1 800 200 200
```

### Expected output format

```
timestamp_in_ms  philosopher_id  action
```

```
0       1 is thinking
0       2 is thinking
1       1 has taken a fork
1       1 has taken a fork
1       1 is eating
201     1 is sleeping
...
800     3 died
```

---

## Implementation

- One **thread** per philosopher.
- One **mutex** per fork.
- A dedicated **monitor** checks timestamps to detect death without data races.
- `gettimeofday` is used for millisecond-precision timing.
- Careful mutex ordering to avoid **deadlock** (odd/even philosophers pick up forks in opposite order).

---

## Makefile Targets

| Target | Description |
|---|---|
| `make` / `make all` | Build `philo` binary |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and binary |
| `make re` | `fclean` + `all` |

---

## Notes

- Written in compliance with the **42 Norm**.
- No `usleep` drift compensation needed if sleep precision is handled carefully.
- Tested with valgrind (`--tool=helgrind`) for data race detection.

---

*42 Heilbronn — Core Curriculum*
