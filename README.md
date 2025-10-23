# Forum Management System in C

> A full-featured discussion forum application with user authentication, threaded messaging, and persistent storage

## 🎯 Overview

A command-line forum management system built in C, demonstrating systems programming concepts including dynamic memory management, file I/O, and complex data structures. Users can create accounts, manage discussion rooms (rubriques), post messages with threaded replies, and search through content.

**Built for**: Advanced C Programming Course | Academic Project | November 2023

## ✨ Key Features

### User Management
- **Two-Tier User System**: 
  - **PROFIL**: Basic user account (can browse and read)
  - **AUTHOR**: PROFIL promoted to author status upon first post
- **Profile Management**: Create, modify, and delete user accounts
- **User Statistics**: Track posting history and activity metrics (authors only)
- **Visitor Mode**: Read-only access without authentication

### Forum Structure
- **Dynamic Rooms (Rubriques)**: Create themed discussion categories
- **Threaded Discussions**: Messages with nested reply chains
- **Room Management**: Modify or delete rooms (author-only)
- **Author Tracking**: See all posts by specific users

### Messaging System
- **Post Messages**: Create new discussion threads
- **Reply to Posts**: Nested reply structure (unlimited depth)
- **Edit & Delete**: Full CRUD operations on owned content
- **Search Functionality**: 
  - Find messages by date
  - Search keywords within messages
  - Filter by author

### Data Persistence
- **File-Based Storage**: Binary file I/O for data persistence
- **Automatic Backup**: Save state on exit
- **Resume Sessions**: Load previous forum state on startup
- **Crash Recovery**: Data integrity through proper file handling

### Analytics
- **Forum Statistics**: Messages per day, active contributors
- **User Analytics**: Post count, activity timeline
- **Room Metrics**: Most active rooms, engagement tracking

## 🏗️ Technical Architecture

### Data Structures

**Core Structures:**
```c
FORUM
├── list_of_authors[]        // Dynamic array of active authors
├── list_of_rubriques[]      // Dynamic array of rooms
├── list_of_profils[]        // All registered users
└── metadata (email, address, etc.)

PROFIL (Basic User Account)
├── ID (subscription ID)
├── first_name, last_name
├── birth_date (DATE)
├── adresse, email
├── phone_number
└── Promoted to AUTHOR upon first post

AUTHOR (extends PROFIL)
├── pseudo (username)
├── profil_author (PROFIL)   // Embedded profile data
├── LSCmsg (linked list)     // User's posted messages
├── number_of_posted_messages
├── date_of_first_posted_message (DATE)
└── date_of_last_posted_message (DATE)

RUBRIQUE (Discussion Room)
├── theme (room name)
├── author (creator)
├── LSCmsg (linked list)     // Messages in this room
└── number_of_messages

MESSAGE
├── title, text, type
├── pseudo_author
├── date (DATE), time
├── LSCreplies (linked list) // Nested replies
└── number_of_replies

DATE (Utility Struct)
├── day, month, year
├── Input/Output functions
├── String conversion utilities
└── Date parsing/formatting
```

**Key Design Decisions:**
- **Two-Tier User System**: Separation between PROFIL (passive users) and AUTHOR (content creators)
  - Users start as PROFIL (can read/browse)
  - Promoted to AUTHOR upon first message post
  - Reduces memory overhead for passive users
- **Linked Lists**: Used for messages/replies to handle dynamic content
- **Dynamic Arrays**: Used for authors/rooms/profils with realloc for scalability
- **Modular Design**: Separate modules for each concern (DATE, PROFIL, AUTHOR, MESSAGE, etc.)
- **Utility Functions**: Reusable DATE module with string conversion and parsing
- **Memory Safety**: Comprehensive malloc/free for leak prevention

### Memory Management

Implemented proper memory lifecycle:
- Dynamic allocation for all variable-length data (strings, lists)
- Careful freeing on program exit (see main.c lines 390-425)
- Prevents memory leaks in nested structures (messages → replies)

### File I/O Strategy

**Two-File System:**
1. **Author File**: Stores all user accounts and profiles
2. **Room File**: Stores discussion rooms and messages

**Operations:**
- `Backup_author()`: Serializes author data to binary file
- `Bring_back_author()`: Deserializes on program start
- `Backup_rub()`: Saves room/message structure
- `Bring_back_rub()`: Restores forum state

## 📁 Project Structure

```
forum-management-system/
├── main.c                   # Entry point, main loop
├── FORUM.c / FORUM.h        # Forum structure and operations
├── AUTHOR.c / AUTHOR.h      # User management
├── PROFIL.c / PROFIL.h      # User profile data
├── RUBRIQUE.c / RUBRIQUE.h  # Discussion room management
├── MESSAGE.c / MESSAGE.h    # Message/reply handling
├── DATE.c / DATE.h          # Date utility functions
├── MENU.c / MENU.h          # CLI menu functions
├── Makefile                 # Build configuration
├── data/
│   ├── authors.dat          # Persistent user data
│   └── rooms.dat            # Persistent forum data
└── README.md
```

## 🚀 Getting Started

### Prerequisites
- GCC compiler (or any C99-compatible compiler)
- Linux/Unix environment (uses `unistd.h`)
- Terminal with ANSI support (for menu display)

### Compilation

```bash
# Compile all source files
gcc -o forum main.c FORUM.c AUTHOR.c PROFIL.c RUBRIQUE.c MESSAGE.c DATE.c MENU.c -std=c99 -Wall

# Alternative: Using a Makefile (if provided)
make
```

### Running the Application

```bash
./forum
```

**First Run:**
- Program will prompt for author and room filenames
- If files don't exist, they'll be created automatically
- You can start with empty data files

**Subsequent Runs:**
- Program loads previous state from data files
- All users, rooms, and messages are restored

## 💻 Usage Examples

### Creating an Account
```
Main Menu → Subscribe (Option 2)
→ Enter profile details
→ Choose username and password
```

### Starting a Discussion
```
Login → Explore → Rooms → Select a Room
→ Add New Message (Option 2)
→ Enter title and content
```

### Replying to Posts
```
Login → Explore → Rooms → Select Room
→ Select Question (Option 1)
→ Reply (Option 1)
```

### Searching Messages
```
Login → Explore → Search by Date (Option 3)
→ Format: "Fri Dec 01"
```

## 🔧 Technical Highlights

### 1. Complex Menu System
Multi-level nested menus with proper state management:
- 18 different choice variables to track menu navigation
- Flag-based flow control (login state, delete account, author promotion)
- Clean menu transitions without state leaks

### 3. Linked List Implementation
Efficient user role management:
```c
PROFIL → registers, can browse
  ↓ (posts first message)
AUTHOR → extends PROFIL with posting capabilities
```
- Lazy initialization pattern (only create AUTHOR when needed)
- Memory efficient (don't allocate message lists for passive users)
- Clean separation of concerns (profile data vs. authoring data)

### 2. Linked List Implementation
Custom implementation for dynamic message storage:
```c
typedef struct nodemsg {
    MESSAGE datamsg;
    struct nodemsg* next;
} nodemsg;
```
- Used for messages, replies (nested lists)
- O(1) insertion, dynamic sizing
- Proper memory cleanup on deletion

### 4. File Persistence Layer
Binary file handling with error checking:
- Check file existence before opening (`access()`)
- Empty file detection (`ftell()`)
- Atomic backup on exit
- Data integrity validation

### 5. Memory Safety
Comprehensive cleanup routine:
- Frees all forum metadata
- Iterates through all authors
- Recursively frees all messages
- Recursively frees all replies per message
- No memory leaks (verified with valgrind)

## 📊 Features in Detail

### Search Functionality
- **Date Search**: Find all messages posted on a specific date
- **Keyword Search**: Search within message content
- **Author Filter**: View all posts by a specific user

### User Permissions
- **Authors**: Can modify/delete their own posts and rooms
- **Visitors**: Read-only access to public content
- **Admins** (forum owner): Can view all user profiles and statistics

### Data Validation
- Input sanitization (newline removal)
- File operation error handling
- User confirmation for destructive actions (delete account, delete room)

## 🐛 Known Limitations

1. **Single-threaded**: No concurrent user support
2. **Binary Files**: Not human-readable, platform-dependent
3. **CLI Only**: No graphical interface
4. **Local Only**: No network/multi-user functionality
5. **Basic Security**: Passwords stored in plaintext (educational project)

## 🔮 Potential Enhancements

- [ ] Multi-user support via network sockets
- [ ] Password hashing (bcrypt/SHA-256)
- [ ] JSON/XML export for data portability
- [ ] Pagination for large message lists
- [ ] Rich text formatting support
- [ ] User-to-user private messaging
- [ ] Room access permissions (private/public)
- [ ] Message voting/rating system
- [ ] SQLite database instead of binary files

## 🛠️ Technologies Used

- **Language**: C (C99 standard)
- **Data Structures**: Linked lists, dynamic arrays
- **File I/O**: Binary file operations (`fopen`, `fread`, `fwrite`)
- **Memory Management**: Manual allocation/deallocation
- **Platform**: POSIX-compliant systems (Linux/Unix)
- **Tools**: GDB for debugging, Valgrind for memory inspection

## 📚 Learning Outcomes

This project demonstrates proficiency in:
- ✅ Advanced C programming (pointers, structs, dynamic memory)
- ✅ Data structure implementation (linked lists, trees)
- ✅ File I/O and persistence
- ✅ Memory management and leak prevention
- ✅ Modular code organization
- ✅ CLI application design
- ✅ Error handling and validation

## 📧 Contact

**Author**: Manar Mighri  
**Email**: manar.mighri@etudiant-enit.utm.tn  
**Date**: November 2023  

---

**Note**: This is an academic project built for educational purposes to demonstrate systems programming concepts in C.

## 📄 License

Educational project - feel free to reference for learning purposes.

---

**Keywords**: C Programming, Data Structures, Linked Lists, File I/O, Memory Management, CLI Application, Forum System, Systems Programming
