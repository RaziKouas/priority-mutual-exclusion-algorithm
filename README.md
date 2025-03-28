# Priority-based Mutual Exclusion Algorithm (PMutex)

![License](https://img.shields.io/badge/license-MIT-blue.svg)

A high-efficiency synchronization primitive that combines FIFO fairness with priority scheduling.

## Table of Contents
- [Key Features](#key-features)
- [Algorithm Overview](#algorithm-overview)
- [Build Instructions](#build-instructions)
- [API Reference](#api-reference)
- [Performance Characteristics](#performance-characteristics)
- [Contributing](#contributing)
- [License](#license)

## Key Features

✔ **Strict Priority Scheduling** - Highest priority wins when timestamps collide  
✔ **Deadlock-free** - Guaranteed progress for all threads  
✔ **Condition Variable Based** - Efficient thread wakeup  
✔ **Lightweight** - Pure POSIX implementation  

## Algorithm Overview

Three-phase selection process:

1. **Queue Insertion** - Timestamped requests with priorities
2. **Winner Selection**:

```c
// 1. Find earliest timestamp
// 2. Select max priority among earliest
```

3. **Atomic Handoff** - Condition variables ensure clean transitions

## Build Instructions

### Compilation

```bash
git clone https://github.com/RaziKouas/priority-mutual-exclusion-algorithm.git
cd priority-mutual-exclusion-algorithm
make
```

### Running Tests

```bash
./pmutex_test
```

## API Reference

### Core Functions

| Function          | Parameters                              | Description                        |
|-------------------|-----------------------------------------|------------------------------------|
| `pmutex_init()`    | `PMutex* m, int capacity`               | Initialize mutex with queue capacity |
| `pmutex_free()`    | `PMutex* m`                             | Release all resources              |
| `pmutex_request()` | `PMutex* m, int pid, int priority`      | Enqueue access request             |
| `pmutex_lock()`    | `PMutex* m, int pid`                    | Block until granted access        |
| `pmutex_unlock()`  | `PMutex* m, int pid`                    | Release critical section          |

### Data Structures

```c
typedef struct {
    pthread_mutex_t lock;
    pthread_cond_t cond;
    Process* queue;     // Priority queue
    int capacity;       // Max queue size
    int size;           // Current queue size
    int current_holder; // PID in critical section (-1 if empty)
} PMutex;

typedef struct {
    int pid;
    int priority;
    struct timeval timestamp;
} Process;
```

## Performance Characteristics

| Operation | Complexity | Notes                        |
|-----------|------------|------------------------------|
| Request   | O(1)       | Lock + append                |
| Lock      | O(n)       | Queue scan + cond wait       |
| Unlock    | O(1)       | Atomic state update          |

## Contributing

We welcome contributions! Please follow these guidelines:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/your-feature`)
3. Commit your changes
4. Push to the branch
5. Open a pull request

## License

MIT © [Razi Kouas] - See LICENSE for details.
