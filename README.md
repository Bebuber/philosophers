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
0    1 is thinking
0    3 is thinking
1    1 has taken a fork
1    1 has taken a fork
1    1 is eating
201  1 is sleeping
...
800  3 died
```

---

## Implementation

### Structure

```
philo/
├── philo.h       # Structs, prototypes, includes
├── main.c        # Entry point, argument validation, cleanup
├── init.c        # Data and philosopher initialisation
├── routine.c     # Philosopher lifecycle: eat, sleep, think — plus thread creation
├── utils.c       # Timing, death detection, print guard
└── ft_atoi.c     # Argument parsing utilities
```

### How it works

**One thread per philosopher.** Each runs the `day()` routine — a loop of eating, sleeping, and thinking until death is detected or the meal limit is reached.

**One mutex per fork.** Philosophers lock their right fork first, then their left. Forks are released immediately after eating.

**Deadlock prevention via staggering.** Even-numbered philosophers delay by `time_to_eat / 2` before their first fork grab (`start_with_thinking`). This gives odd philosophers a head start and prevents all philosophers from grabbing one fork simultaneously and deadlocking.

**Precise sleeping.** Instead of a raw `usleep`, `ft_sleep` polls `gettimeofday` in a tight loop with 100µs granularity and exits early if a death is detected — preventing threads from oversleeping past their time window.

**Death detection without races.** A dedicated monitor (`monitor_philos`) runs in the main thread after all philosopher threads are created. It continuously checks each philosopher's `last_meal` timestamp under `meal_mutex`, and prints the death message and sets `data->death` under `death_mutex` + `print` mutex to prevent interleaved output.

**Print guard.** `try_print` checks for death under the print mutex before printing, ensuring no state messages are logged after a philosopher has died.

### Key data structures

```c
typedef struct s_philo
{
    int             id;
    pthread_t       thread;
    int             right_fork;   // index into data->forks[]
    int             left_fork;    // index into data->forks[]
    int             nb_meals;     // meal limit (-1 if unlimited)
    int             meals;        // meals eaten so far
    unsigned long   last_meal;    // timestamp of last meal start (ms)
    unsigned long   time_to_die;
    unsigned long   time_to_eat;
    unsigned long   time_to_sleep;
    int             nb_philos;
    t_data          *data;        // back-pointer to shared state
}   t_philo;

typedef struct s_data
{
    int             nb_philo;
    int             nb_forks;
    unsigned long   tm_to_die;
    int             tm_to_eat;
    int             tm_to_sleep;
    int             nb_meals;
    int             death;        // set to 1 when a philosopher dies
    unsigned long   start;        // simulation start timestamp
    t_philo         *philo;
    pthread_mutex_t *forks;
    pthread_mutex_t meal_mutex;   // protects last_meal and meals count
    pthread_mutex_t death_mutex;  // protects data->death flag
    pthread_mutex_t print;        // ensures non-interleaved output
}   t_data;
```

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
- Uses `gettimeofday` for millisecond-precision timing.
- `ft_sleep` uses a polling loop rather than raw `usleep` to avoid timing drift and enable early exit on death.
- The 1-philosopher edge case is handled separately: the philosopher picks up one fork, waits `time_to_die` ms, and dies.

---

*42 Heilbronn — Core Curriculum*
