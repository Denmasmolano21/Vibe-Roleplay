# Changelog - Vibe Roleplay Gamemode

## Perubahan Struktur & Fitur Baru

### 1. Sistem Admin Help (/ahelp)
- Menu bantuan admin lengkap dengan 5 kategori
- Semua command admin terorganisir dengan baik
- Dialog menggunakan DIALOG_STYLE_TABLIST (bukan MSGBOX)

### 2. Sistem Report & Ask
- `/report [laporan]` - Player bisa laporkan masalah ke admin
- `/ask [pertanyaan]` - Player bisa tanya admin
- Admin online akan menerima notifikasi real-time
- Semua report tersimpan di log file

### 3. Admin Communication
- `/a [pesan]` - Chat khusus admin
- `/reply [playerid] [pesan]` - Admin bisa balas report/ask player
- Level admin ditampilkan di chat admin

### 4. Admin Level System
- Max admin level: 7 (bisa diubah di config)
- Sistem GUARD_ADMIN_LEVEL untuk command tertentu
- Validasi level saat setadmin

### 5. Admin Log System
- File: `scriptfiles/admin_logs.txt`
- Semua aksi admin tercatat dengan timestamp
- Format: [DD/MM/YYYY HH:MM:SS] [ADMIN: Name (ID)] action
- Report log: `scriptfiles/report_logs.txt`

### 6. Command Admin Baru
**Player Management:**
- `/freeze` - Freeze player
- `/unfreeze` - Unfreeze player
- `/slap` - Slap player
- `/ban` - Ban player
- `/setadmin` - Set admin level (0-7)
- `/sethealth` - Set health player
- `/setarmour` - Set armour player
- `/setskin` - Set skin player
- `/giveweapon` - Berikan weapon
- `/resetweapon` - Reset weapon player

**Vehicle Admin:**
- `/aveh` - Spawn kendaraan admin
- `/delveh` - Hapus kendaraan
- `/repair` - Repair kendaraan
- `/flip` - Balikkan kendaraan
- `/respawnallveh` - Respawn semua kendaraan kosong

**Teleport:**
- `/goto` - Teleport ke player
- `/gethere` - Teleport player ke admin
- `/tp` - Teleport ke koordinat

**Server Management:**
- `/announce` - Kirim announcement
- `/gmx` - Restart gamemode

### 7. Perbaikan Dialog
- Semua dialog MSGBOX diubah ke TABLIST
- `/stats` - Menggunakan TABLIST
- `/mypos` - Menggunakan TABLIST
- `/help` - Semua kategori menggunakan TABLIST

### 8. Struktur File Terorganisir
**cmd_admin.inc:**
- Section: Admin Help
- Section: Basic Admin Commands
- Section: Player Management
- Section: Stats Management
- Section: Vehicle Admin
- Section: Teleport Commands
- Section: Server Management
- Section: Admin Communication

**cmd_general.inc:**
- Section: Help Command
- Section: Report & Ask System
- Section: Stats Commands
- Section: Action Commands

**File Baru:**
- `utils/admin_log.inc` - Sistem logging admin
- `ADMIN_COMMANDS.md` - Dokumentasi lengkap
- `CHANGELOG.md` - Catatan perubahan

### 9. Config Updates
- `MAX_ADMIN_LEVEL` = 7
- `ADMIN_LOG_FILE` = "admin_logs.txt"
- `REPORT_LOG_FILE` = "report_logs.txt"

### 10. Dialog IDs Baru
- `DIALOG_REPORT` = 250
- `DIALOG_ASK` = 251
- `DIALOG_AHELP_CATEGORY` = 302
- `DIALOG_AHELP_BASIC` = 303
- `DIALOG_AHELP_PLAYER` = 304
- `DIALOG_AHELP_VEHICLE` = 305
- `DIALOG_AHELP_TELEPORT` = 306
- `DIALOG_AHELP_MANAGEMENT` = 307

## Fitur Yang Sudah Ada & Terstruktur
- Sistem auth (login/register)
- Sistem stats (hunger/thirst)
- Sistem vehicle (engine, lights, lock, park)
- Sistem spawn
- Sistem mapping
- Sistem session
- Database MySQL

## Notes
- Tidak ada simbol yang tidak didukung
- Semua file terstruktur dengan section comments
- Code mudah dibaca dan dikembangkan
- Log system otomatis untuk semua admin actions
