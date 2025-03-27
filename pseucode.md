# Priority-based Mutual Exclusion Algorithm - Pseudocode

### Variables
- **queue**: Priority queue (FIFO by default)
- **lock**: Mutex lock

### `request_access(process_id, priority)`
1. **lock(queue)**
2. Add `(process_id, priority, timestamp)` to the queue.
3. **unlock(queue)**

### `grant_access()`
1. Loop indefinitely:
   - **lock(queue)**
   - If the queue is not empty:
     - Extract all processes with the **earliest timestamp**.
     - If only one process:
       - **selected_process** ← that process.
     - Else:
       - **selected_process** ← process with the **highest priority**.
     - Remove **selected_process** from the queue.
     - **unlock(queue)**.

     - **Critical section**:
       - Allow the **selected_process** to execute.
       - Wait for the **selected_process** to finish.
       - End critical section.
   - Else:
     - **unlock(queue)**.
     - Sleep for a small delay.

### `release_access(process_id)`
- The process exits the critical section.
