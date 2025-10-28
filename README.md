Automated Attendance System — Backend (Prototype) v0.1

SIH-2025 Problem Statement No. 25012 — Prototype
This repository contains the first prototype backend for an automated attendance system that marks attendance by comparing two images (student photo vs captured image). The project is implemented as a native prototype (C++ / OpenCV style) and built with CMake. The repository contains source code, build files, and image data used by the prototype.

```markdown
# 🚀 Automated Attendance System – Backend (Prototype v0.1)

> **Smart India Hackathon 2025 – Problem Statement #25012**  
> *Automated Attendance System for Rural Schools*

---

## 🧭 About the Project

This project is a **backend prototype** for an Automated Attendance System built for **SIH 2025**.  
It aims to simplify attendance management in rural schools by using **image processing and facial recognition** techniques to automatically mark attendance from captured classroom images.

The idea is simple — teachers take a photo, the system compares faces with the registered student images, and marks attendance automatically.

---

## 🎯 Project Goals

- Reduce manual effort and errors in attendance tracking  
- Work efficiently in low-resource rural environments  
- Support offline attendance marking and later sync with cloud  
- Lay the foundation for a complete AI-based attendance solution

---

## ⚙️ Tech Stack

| Component | Technology |
|------------|-------------|
| **Language** | C++ |
| **Build System** | CMake |
| **Library** | OpenCV (for image processing & face comparison) |
| **Database** | SQLite (`images.db`) |
| **Docs** | Doxygen |
| **Version Control** | Git + GitHub |

---

## 📁 Project Structure

```

Automated-Attendance-System-Backend_v.01/
├── src/             # Source code files (core logic)
├── include/         # Header files
├── images.db        # SQLite database (student & attendance data)
├── CMakeLists.txt   # Build configuration
├── Doxyfile         # Documentation config
├── html/ , latex/   # Auto-generated documentation (optional)
└── README.md        # This file

````

---

## 🧩 Requirements

Make sure you have the following installed before building:

- **CMake ≥ 3.10**
- **C++17 or higher**
- **OpenCV ≥ 4.0**
- **SQLite3**

For Ubuntu users:
```bash
sudo apt update
sudo apt install build-essential cmake libopencv-dev sqlite3
````

For macOS (Homebrew):

```bash
brew install cmake opencv sqlite
```

---

## 🛠️ How to Build & Run

```bash
# Clone the repository
git clone https://github.com/Abhinav-Who/Automated-Attendance-System-Backend_v.01.git
cd Automated-Attendance-System-Backend_v.01

# Create a build directory
mkdir build && cd build

# Configure the project
cmake ..

# Build the project
cmake --build . --config Release

# Run the program (replace with the actual binary name)
./attendance_backend
```

---

## 🧪 Example Usage

Compare two images — one stored reference image and one captured classroom image:

```bash
./attendance_backend --ref student_photo.jpg --input classroom_image.jpg
```

**Sample Output:**

```
✅ Match Found: Mahima Tomar
✅ Match Score: 0.92
✅ Attendance Marked: PRESENT
```

---

## 🗃️ Database Overview

* **Database File:** `images.db`
* **Tables:**

  * `students` → stores student IDs, names, and reference image paths
  * `attendance` → stores date/time and presence status

The system reads the registered students from `images.db`, performs face matching, and automatically updates their attendance records.

---

## 📘 Documentation

To generate documentation using Doxygen:

```bash
doxygen Doxyfile
```

HTML and LaTeX docs will be generated inside the `html/` and `latex/` folders.

---

## 🌟 Future Plans

* Integrate with a **Flutter mobile app** for teachers
* Add **cloud sync** via Firebase or AWS
* Replace simple matching with **AI-based facial recognition**
* Include **real-time camera detection** and live reporting
* Add **admin dashboard** for attendance analytics

---

## 👥 Team & Contributors

* **Abhinav Tomar** – Developer & Prototype Designer
* **Team (SIH 2025)** – Collaboration and field testing

> Special thanks to mentors and organizers of **Smart India Hackathon 2025** for guidance and motivation.

---

## 🧾 License

This project is currently under development for **SIH 2025** and is not yet licensed for open-source distribution.
You may reuse or fork this prototype with proper credit to the authors and team.

---

## 💡 Inspiration

> “Technology should make teachers’ lives easier and learning more efficient — not the other way around.”

This project is a small step toward bringing **AI-driven automation** to rural education systems, making attendance tracking faster, smarter, and more transparent.

---

**© 2025 Abhinav Tomar & Team – All Rights Reserved**

```

---

Would you like me to also give you the exact commands to **add, commit, and push this README.md** to your GitHub repo right now?
```
