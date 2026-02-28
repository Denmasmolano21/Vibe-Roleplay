# Admin Commands Documentation

## 🎮 Interactive Admin Menu

### `/admin` - Menu Admin Interaktif (RECOMMENDED)
Menu lengkap dengan dialog interaktif untuk semua fungsi admin. Tidak perlu hafal command!

**Fitur:**
- Player Management (kick, ban, freeze, dll)
- Player Stats (money, level, health, dll)
- Vehicle Admin (spawn, delete, repair, dll)
- Teleport (goto, gethere, coords)
- Reports (lihat & balas)
- Server Management (announce, gmx, dll)

**Keunggulan:**
- ✅ Tidak perlu hafal command
- ✅ Tidak perlu ingat player ID
- ✅ Input validation otomatis
- ✅ User-friendly dengan dialog
- ✅ Semua tercatat di log

Lihat [INTERACTIVE_ADMIN_GUIDE.md](INTERACTIVE_ADMIN_GUIDE.md) untuk panduan lengkap.

---

## Admin Level System
- Level 0: Player biasa
- Level 1-7: Admin dengan akses berbeda

## Command List

### Interactive Menu (Recommended)
- `/admin` - Menu admin interaktif lengkap dengan dialog

### Help & Communication
- `/ahelp` - Menu bantuan admin lengkap
- `/a [pesan]` - Chat admin (hanya admin yang bisa lihat)
- `/reports` - Lihat semua report/ask dengan dialog interaktif
- `/clearreports` - Hapus semua report/ask yang aktif

### Player Management
- `/kick [playerid] [alasan]` - Kick player dari server
- `/ban [playerid] [alasan]` - Ban player dari server
- `/freeze [playerid]` - Freeze player
- `/unfreeze [playerid]` - Unfreeze player
- `/slap [playerid] [alasan]` - Slap player
- `/setadmin [playerid] [level]` - Set admin level (0-7)

### Player Stats
- `/sethealth [playerid] [amount]` - Set health player
- `/setarmour [playerid] [amount]` - Set armour player
- `/setskin [playerid] [skinid]` - Set skin player
- `/giveweapon [playerid] [weaponid] [ammo]` - Berikan weapon
- `/resetweapon [playerid]` - Reset semua weapon player
- `/givemoney [playerid] [amount]` - Berikan uang
- `/setlevel [playerid] [level]` - Set level player
- `/sethunger [playerid] [amount]` - Set hunger player
- `/setthirst [playerid] [amount]` - Set thirst player

### Vehicle Commands
- `/aveh [vehicleid] [color1] [color2]` - Spawn kendaraan admin
- `/delveh` - Hapus kendaraan yang sedang dikendarai
- `/repair` - Repair kendaraan
- `/flip` - Balikkan kendaraan
- `/respawnallveh` - Respawn semua kendaraan kosong

### Teleport Commands
- `/goto [playerid]` - Teleport ke player
- `/gethere [playerid]` - Teleport player ke kamu
- `/tp [x] [y] [z]` - Teleport ke koordinat

### Server Management
- `/announce [pesan]` - Kirim announcement ke semua player
- `/gmx` - Restart gamemode

## Player Commands

### Help & Support
- `/help` - Menu bantuan player
- `/report [laporan]` - Laporkan masalah ke admin (min 10 karakter)
- `/ask [pertanyaan]` - Tanya admin (min 10 karakter)

## Report & Ask System

### Cara Kerja untuk Player:
1. Player gunakan `/report [laporan]` atau `/ask [pertanyaan]`
2. Sistem akan memberikan ID report (contoh: #5)
3. Admin online akan menerima notifikasi
4. Report tersimpan sampai admin membalas

### Cara Kerja untuk Admin:
1. Admin menerima notifikasi saat ada report/ask baru
2. Admin gunakan `/reports` untuk melihat semua report/ask
3. Dialog akan menampilkan list dengan informasi:
   - ID Report
   - Type (REPORT atau ASK)
   - Nama Player
   - Preview pesan
4. Pilih report untuk melihat detail lengkap:
   - Dari siapa (nama & ID)
   - Kategori (REPORT/ASK)
   - Waktu (berapa lama yang lalu)
   - Pesan lengkap
5. Klik "Balas" untuk membalas
6. Ketik balasan dan kirim
7. Report otomatis terhapus setelah dibalas
8. Player akan menerima balasan dari admin

### Fitur Dialog:
- List report dengan preview
- Detail lengkap setiap report
- Input balasan langsung dari dialog
- Warna berbeda untuk REPORT (merah) dan ASK (biru)
- Timestamp otomatis
- Auto-remove setelah dibalas

### Stats & Info
- `/stats` - Lihat statistik kamu
- `/mypos` - Lihat posisi kamu

### Actions
- `/eat` - Makan untuk menambah hunger
- `/drink` - Minum untuk menambah thirst

## Log System
Semua aksi admin akan tersimpan di:
- `scriptfiles/admin_logs.txt` - Log semua command admin
- `scriptfiles/report_logs.txt` - Log semua report dari player

## Notes
- Semua dialog menggunakan DIALOG_STYLE_TABLIST
- Tidak ada simbol yang tidak didukung
- Sistem terstruktur dan mudah dikembangkan
