# 🎮 Vibe Roleplay - Interactive Systems

## 🌟 Overview

Vibe Roleplay sekarang memiliki **7 sistem interaktif lengkap** dengan interface user-friendly! Semua sistem menggunakan dialog menu yang mudah dipahami, sehingga pemain tidak perlu hafal command panjang.

---

## ✨ Sistem yang Tersedia

### 1. 🚗 Vehicle System
Kelola kendaraan dengan mudah melalui menu interaktif.
- **Command:** `/v`
- **Features:** Engine, lights, lock, park, fuel, my vehicles
- **File:** `gamemodes/commands/cmd_vehicle.inc`

### 2. 🎒 Inventory System
Sistem inventory dengan 20 slot dan berbagai jenis item.
- **Command:** `/inv` atau `/i`
- **Features:** Use items, give items, drop items, stackable
- **File:** `gamemodes/modules/inventory/inventory.inc`

### 3. 📱 Phone System
Sistem telepon lengkap dengan call, SMS, dan contacts.
- **Command:** `/phone` atau `/p`
- **Features:** Call, SMS, contacts, history
- **File:** `gamemodes/modules/phone/phone.inc`

### 4. 🏠 House System
Beli, jual, dan kelola rumah dengan mudah.
- **Command:** `/house`
- **Features:** Buy/sell, lock, interior, storage
- **File:** `gamemodes/modules/house/house.inc`

### 5. 🏢 Business System
Kelola bisnis dan dapatkan passive income.
- **Command:** `/business` atau `/biz`
- **Features:** Buy/sell, safe, employees, products
- **File:** `gamemodes/modules/business/business.inc`

### 6. 💼 Job System
8 jenis pekerjaan dengan salary dan missions.
- **Command:** `/job`
- **Features:** 8 jobs, duty system, salary, missions
- **File:** `gamemodes/modules/job/job.inc`

### 7. 👥 Faction System
Bergabung dengan faction dan naik rank.
- **Command:** `/faction`
- **Features:** Multiple factions, ranks, chat, HQ
- **File:** `gamemodes/modules/faction/faction.inc`

---

## 🚀 Quick Start

### Untuk Player
1. Login ke server
2. Ketik `/help` untuk melihat bantuan
3. Gunakan command menu seperti `/v`, `/inv`, `/phone`
4. Explore semua fitur melalui menu interaktif!

### Untuk Admin
1. Login sebagai admin
2. Ketik `/admin` untuk membuka admin panel
3. Pilih kategori yang ingin dikelola
4. Semua fitur admin ada di menu!

---

## 📚 Dokumentasi

### File Dokumentasi
- **INTERACTIVE_SYSTEM_GUIDE.md** - Panduan lengkap semua sistem
- **COMMAND_REFERENCE.md** - Daftar semua command
- **SYSTEM_UPDATE_SUMMARY.md** - Summary update sistem
- **ADMIN_COMMANDS.md** - Dokumentasi admin commands

### File Sistem
```
gamemodes/
├── modules/
│   ├── inventory/inventory.inc
│   ├── phone/phone.inc
│   ├── house/house.inc
│   ├── business/business.inc
│   ├── job/job.inc
│   └── faction/faction.inc
│
├── commands/
│   ├── cmd_vehicle.inc
│   ├── cmd_inventory.inc
│   ├── cmd_phone.inc
│   ├── cmd_house.inc
│   ├── cmd_business.inc
│   ├── cmd_job.inc
│   └── cmd_faction.inc
│
└── utils/
    └── dialog_handler_extended.inc
```

---

## 🎯 Fitur Utama

### User-Friendly
✅ Dialog menu untuk semua sistem  
✅ Tidak perlu hafal command panjang  
✅ Navigasi intuitif  
✅ Info lengkap di setiap menu  

### Konsisten
✅ Semua sistem ikuti pola yang sama  
✅ Warna dan format seragam  
✅ Command alternatif pendek  
✅ Feedback message jelas  

### Roleplay Friendly
✅ Action messages otomatis  
✅ Nearby messages untuk interaksi  
✅ Realistic features (fuel, hunger, thirst)  
✅ Economy system terintegrasi  

---

## 💡 Command Cheat Sheet

### Player Commands
| System | Command | Alias |
|--------|---------|-------|
| Vehicle | `/v` | `/vehicle` |
| Inventory | `/inv` | `/i`, `/inventory` |
| Phone | `/phone` | `/p` |
| House | `/house` | - |
| Business | `/business` | `/biz` |
| Job | `/job` | - |
| Faction | `/faction` | - |

### Admin Commands
| Function | Command |
|----------|---------|
| Admin Panel | `/admin` atau `/pm` |
| Admin Help | `/ahelp` |
| Admin Chat | `/a [pesan]` |
| Reports | `/reports` |

---

## 🔧 Installation

1. **Copy Files**
   ```
   Copy semua file ke folder gamemode kamu
   ```

2. **Update gamemode.pwn**
   ```pawn
   // Sudah otomatis ter-include di gamemode.pwn
   #include "modules\inventory\inventory.inc"
   #include "modules\phone\phone.inc"
   #include "modules\house\house.inc"
   #include "modules\business\business.inc"
   #include "modules\job\job.inc"
   #include "modules\faction\faction.inc"
   ```

3. **Compile**
   ```
   Compile gamemode.pwn dengan PAWN compiler
   ```

4. **Run Server**
   ```
   Start server dan test semua fitur!
   ```

---

## 📊 Statistics

- **Total Systems:** 7 sistem lengkap
- **Total Commands:** 30+ commands
- **Total Dialogs:** 50+ dialog menus
- **Total Files:** 15+ new files
- **Lines of Code:** 2500+ lines

---

## 🎮 Testing

### Test Checklist
- [ ] Vehicle system (/v)
- [ ] Inventory system (/inv)
- [ ] Phone system (/phone)
- [ ] House system (/house)
- [ ] Business system (/business)
- [ ] Job system (/job)
- [ ] Faction system (/faction)
- [ ] Admin panel (/admin)

---

## 🐛 Known Issues

### Coming Soon
- House storage system
- Business product management
- Job missions
- Faction territories
- Advanced phone features
- Vehicle trunk system

### Need Testing
- All dialog responses
- Database integration
- Permission checks
- Cooldown systems

---

## 🤝 Contributing

Jika kamu ingin menambahkan fitur atau memperbaiki bug:

1. Test fitur yang ada
2. Buat fitur baru mengikuti pola yang sama
3. Update dokumentasi
4. Submit changes

---

## 📞 Support

Jika ada pertanyaan atau masalah:
- Baca dokumentasi lengkap di `INTERACTIVE_SYSTEM_GUIDE.md`
- Check command reference di `COMMAND_REFERENCE.md`
- Lihat update summary di `SYSTEM_UPDATE_SUMMARY.md`

---

## 📝 Changelog

### Version 1.0.3 - Interactive Systems Update
- ✅ Added Inventory System
- ✅ Added Phone System
- ✅ Added House System
- ✅ Added Business System
- ✅ Added Job System
- ✅ Added Faction System
- ✅ Enhanced Vehicle System
- ✅ User-friendly dialog menus for all systems
- ✅ Complete documentation

---

## 🎉 Credits

**Vibe Roleplay Development Team**
- Gamemode: Denmasmolano
- Systems: Interactive & User-Friendly
- Version: 1.0.3

---

## 📜 License

Vibe Roleplay © 2024
All rights reserved.

---

**Selamat bermain dan nikmati semua fitur baru! 🎮**

