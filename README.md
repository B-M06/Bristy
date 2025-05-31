

## 📝 **DSA Lab Report**

**Project Title:** *Airline Reservation System using Hashing, Binary Search & Queues in C++*

---

### 🔍 **1. Introduction**

The airline reservation system is an essential tool for efficiently managing bookings in real-world airline operations. This project demonstrates a simplified console-based reservation system using **Data Structures and Algorithms (DSA)**. It allows booking and cancellation of flight seats, manages a waiting list using queue logic, and supports fast name lookups using hashing and binary search.

---

### 🎯 **2. Objective**

* To develop a reservation system for an airline that supports:

  * Booking of available seats
  * Cancellation of reserved seats
  * Management of a waiting list
  * Fast name searching using hashing and binary search

* To apply **DSA concepts** like arrays, hashing, binary search, and queue in a real-life inspired application.

---

### 🛠️ **3. Tools and Purpose**

| Tool / Technology | Purpose                                                 |
| ----------------- | ------------------------------------------------------- |
| C++               | Programming language used for logic implementation      |
| Code::Blocks IDE  | IDE used for writing, compiling, and debugging the code |
| Arrays            | For storing booked seats and the waiting list           |
| Hash Table        | For efficient name-based search                         |
| Binary Search     | For searching cancelled passengers                      |
| Queue Logic       | For managing waiting list in FIFO order                 |

---

### 🔄 **4. Methodology**

#### 📌 Core Concepts Used:

* **Arrays**: For storing 10 seats and 5 waiting list entries.
* **Hashing**: To map passenger names to indices using a simple hash function with linear probing.
* **Binary Search**: For sorted name search during cancellation.
* **Queue (using array)**: For the waiting list (FIFO).

---

### 💡 **5. Code Breakdown and Explanation**

#### ✅ `bookTicket(string name)`

* Searches for an empty seat.
* If found, assigns the seat and stores the name in the hash table.
* If full, adds the name to the waiting list (max 5 names).

#### ❌ `cancelTicket(string name)`

* Searches the seat using **binary search** on a sorted name list.
* If not found, uses the **hash table**.
* On successful cancellation, moves the **first name from the waiting list** to the vacant seat.

#### 🔍 `insertToHash()` & `searchHash()`

* Simple **additive hash function** with **linear probing**.
* Maps name to a seat index for fast lookup.

#### 📊 `displaySeats()`

* Prints all booked seats and waiting list passengers.

#### 🧠 `main()`

* Provides a menu for user to:

  * Book a ticket
  * Cancel a ticket
  * View all bookings
  * Exit the program

---

### 🖥️ **6. Sample Output**

```
--- Airline Reservation System ---
1. Book Ticket
2. Cancel Ticket
3. Display Bookings
4. Exit
Enter your choice: 1
Enter passenger name: Alice
Seat booked for Alice at Seat 1

--- Airline Reservation System ---
1. Book Ticket
2. Cancel Ticket
3. Display Bookings
4. Exit
Enter your choice: 3

--- Booked Seats ---
Seat 1: Alice

--- Waiting List ---
```

---

### ✅ **7. Conclusion**

This project successfully simulates a real-world airline reservation system using core data structures. It demonstrates:

* Efficient searching through hashing and binary search
* Proper management of resources using array-based queues
* Real-time update and display of booking status

It deepened our understanding of **hashing**, **search algorithms**, and **queue management** in practical scenarios.

---

### 📚 **8. References**

* Data Structures and Algorithms Textbook by Reema Thareja
* GeeksforGeeks: [Hashing](https://www.geeksforgeeks.org/hashing-data-structure/)
* C++ Documentation: [cplusplus.com](https://cplusplus.com/)
* Class Notes and Lab Guidelines

---



