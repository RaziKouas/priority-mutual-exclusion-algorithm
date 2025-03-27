# Priority-based Mutual Exclusion Algorithm (PMutex)

![License](https://img.shields.io/badge/license-MIT-blue.svg)

A high-efficiency synchronization primitive that combines FIFO fairness with priority scheduling. Perfect for systems where critical section access needs both fairness and priority awareness.

## Table of Contents
- [Key Features](#key-features)
- [Algorithm Overview](#algorithm-overview)
- [Quick Start](#quick-start)
- [Build Instructions](#build-instructions)
- [API Reference](#api-reference)
- [Performance Characteristics](#performance-characteristics)
- [Contributing](#contributing)
- [License](#license)

## Key Features

✔ **Priority-aware scheduling** - Higher priority processes get precedence when timestamps collide  
✔ **Starvation-free** - Guarantees eventual access for all processes  
✔ **Thread-safe implementation** - Robust mutex protection for all queue operations  
✔ **Lightweight** - Pure C implementation with minimal dependencies  

## Algorithm Overview

The PMutex algorithm works through three core components:

1. **Priority Queue** - Stores pending requests with (PID, priority, timestamp) tuples
2. **FIFO Baseline** - By default, processes are granted access in arrival order
3. **Priority Escalation** - When multiple requests arrive at the same time, highest priority wins

```c
// Simplified core logic
while (true) {
    lock(queue);
    if (!empty(queue)) {
        ProcessEntry entry = find_oldest_highest_priority(queue);
        grant_access(entry.pid);
        unlock(queue);
        execute_critical_section(entry.pid);
    } else {
        unlock(queue);
        sleep(SHORT_DELAY);
    }
}
```
Full pseudocode available in [ALGORITHM.md](ALGORITHM.md).

## Quick Start

### Basic Usage

```c
#include "pmutex.h"

PMutex m;
pmutex_init(&m);

// Thread 1
pmutex_request(&m, 1001, HIGH_PRIORITY);
pmutex_wait(&m);
/* Critical section */
pmutex_release(&m);

// Thread 2
pmutex_request(&m, 1002, LOW_PRIORITY);
pmutex_wait(&m);
/* Critical section */
pmutex_release(&m);
```

### Sample Output

```
[PMutex] Process 1001 (PRIO 2) entered critical section
[PMutex] Process 1001 released lock after 15ms
[PMutex] Process 1002 (PRIO 1) entered critical section
```

## Build Instructions

### Prerequisites

- GCC or Clang
- POSIX threads library

### Compilation

```bash
git clone https://github.com/yourusername/Priority-based-Mutual-Exclusion-Algorithm.git
cd Priority-based-Mutual-Exclusion-Algorithm
make
```

### Running Tests

```bash
./build/pmutex_test
```

## API Reference

### Core Functions

| Function            | Description                         |
|---------------------|-------------------------------------|
| `pmutex_init()`      | Initialize PMutex instance         |
| `pmutex_request()`   | Submit access request with priority |
| `pmutex_wait()`      | Block until access granted         |
| `pmutex_release()`   | Release critical section           |

### Priority Levels

```c
#define PRIO_CRITICAL 4   // System-critical tasks
#define PRIO_HIGH     3
#define PRIO_NORMAL   2   // Default
#define PRIO_LOW      1
#define PRIO_BACKGROUND 0 // Non-urgent tasks
```

## Performance Characteristics

| Operation | Time Complexity | Notes                        |
|-----------|-----------------|------------------------------|
| Request   | O(1)            | Constant time enqueue        |
| Grant     | O(n)            | Linear scan for oldest+highest |
| Release   | O(1)            | Simple state update          |

For systems with >1000 concurrent threads, consider the heap-based variant in `pmutex_advanced.c`.

## Contributing

We welcome contributions! Please follow these guidelines:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/your-feature`)
3. Commit your changes
4. Push to the branch
5. Open a pull request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
