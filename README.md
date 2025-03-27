# Priority-based Mutual Exclusion Algorithm

This is an implementation of a **priority-based mutual exclusion algorithm** designed to manage access to a critical section. The algorithm uses a **priority queue** and **mutex locking** mechanism to control process access in a fair and efficient way.

---

## 📝 Overview

This algorithm provides a way to grant and release access to a critical section based on the **arrival timestamp** of processes. It ensures that:

- Processes are granted access to the critical section based on their **arrival timestamp**.
- If multiple processes have the same timestamp, the process with the **higher priority** is granted access first.
- **Mutual exclusion** is maintained, meaning no two processes can execute in the critical section at the same time.
- The system prevents **starvation** by granting access in a fair manner.

---

## ⚙️ Features

- **FIFO Queue**: The algorithm uses a **priority queue** (FIFO by default) to manage processes.
- **Timestamp-based Scheduling**: Processes are granted access based on their **arrival timestamp**. If two processes have the same timestamp, the one with the **higher priority** is chosen.
- **Mutex Locking**: A **mutex lock** is used to ensure that the queue is accessed safely, preventing race conditions.

---

## 🔧 Functions

### `request_access(process_id, priority)`

This function allows a process to request access to the critical section. The process is added to the queue with its **priority** and **timestamp**.

### `grant_access()`

This function continuously checks the queue for processes waiting for access. It grants access to the process with the **earliest arrival timestamp**. If multiple processes have the same timestamp, the process with the **higher priority** is selected.

### `release_access(process_id)`

This function is called when a process has finished executing in the critical section, releasing its access.

---

## 🛠️ How It Works

1. A process calls `request_access()` to join the queue with its **ID**, **priority**, and **timestamp**.
2. The `grant_access()` function grants access based on the **arrival timestamp**. If multiple processes have the same timestamp, the process with the **higher priority** is granted access first.
3. Once a process is done executing in the critical section, it calls `release_access()`.

---

## 🚀 Usage

You can integrate this algorithm into your projects to handle process synchronization and mutual exclusion in a **timestamp-based** manner. Simply include the algorithm code and call the functions as needed to manage critical section access.

---

## 📝 License

This project is **open source** and released under the **MIT License**. Feel free to use, modify, and distribute the code!
