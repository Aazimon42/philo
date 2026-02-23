*This project has been created as part of the 42 curriculum by edi-maio*

# philosophers

## Description

Philosophers is a multithreading project based on the classic Dining Philosophers Problem.
The goal is to simulate philosophers sitting around a table who alternate between eating, sleeping, and thinking, while sharing forks (mutexes) placed between them.
The project focuses on thread management, mutexes, and safe memory handling using pthreads.

## Instructions

### Compilation

Compile the project using:

```bash
make
```

### Execution

Run the program by passing a list of integers as arguments:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

## Resources

### References

- Official philosophers subject (42 intranet)
- Documentation on pthreads and mutexes

### Use of AI

Artificial intelligence was used to find potential error causes and generate tests, explaining the expected results in each case.
All algorithmic choices, implementations, and debugging were performed manually, and no code was directly copied from AI-generated content.
