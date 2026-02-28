# Update Notes - Report & Ask System dengan Dialog

## Perubahan Terbaru

### Sistem Report/Ask Interaktif dengan Dialog

Sistem report/ask sekarang menggunakan dialog interaktif yang lebih user-friendly untuk admin.

### Fitur Baru:

#### 1. Report System dengan Penyimpanan
- Report/ask tersimpan di memory (max 50)
- Setiap report memiliki ID unik
- Timestamp otomatis
- Kategori: REPORT (merah) atau ASK (biru)

#### 2. Command `/reports` untuk Admin
Admin bisa melihat semua report/ask dalam bentuk dialog dengan informasi:
- ID Report
- Type (REPORT/ASK)
- Nama Player
- Preview pesan (28 karakter pertama)

#### 3. Dialog Detail Report
Saat admin pilih report, akan muncul detail lengkap:
- Dari siapa (nama & ID player)
- Kategori (REPORT/ASK dengan warna)
- Waktu (berapa lama yang lalu)
- Pesan lengkap

#### 4. Dialog Reply
Admin bisa langsung balas dari dialog:
- Input text untuk balasan
- Otomatis kirim ke player
- Report terhapus setelah dibalas
- Notifikasi jika masih ada report lain

#### 5. Command `/clearreports`
Admin bisa hapus semua report/ask sekaligus

### File Baru:
- `gamemodes/utils/report_system.inc` - Core sistem report
- `REPORT_SYSTEM_GUIDE.md` - Panduan lengkap
- `UPDATE_NOTES.md` - Catatan update ini

### File Dimodifikasi:
- `gamemodes/commands/cmd_general.inc` - Update /report dan /ask
- `gamemodes/commands/cmd_admin.inc` - Tambah /reports dan /clearreports
- `gamemodes/utils/dialog_handler.inc` - Handler dialog report
- `gamemodes/config/dialog_ids.inc` - Tambah dialog IDs
- `gamemodes/gamemode.pwn` - Include report_system
- `ADMIN_COMMANDS.md` - Update dokumentasi

### Dialog IDs Baru:
```pawn
#define DIALOG_REPORTS_LIST         252
#define DIALOG_REPORT_VIEW          253
#define DIALOG_REPORT_REPLY         254
```

### Cara Kerja:

**Player:**
1. `/report [pesan]` atau `/ask [pesan]`
2. Dapat ID report (contoh: #5)
3. Tunggu balasan admin

**Admin:**
1. Terima notifikasi saat ada report baru
2. `/reports` untuk lihat list
3. Pilih report untuk lihat detail
4. Klik "Balas" untuk membalas
5. Ketik balasan dan kirim
6. Report otomatis terhapus

### Keunggulan Sistem Baru:

✅ Dialog interaktif (tidak perlu ketik ID manual)
✅ Preview pesan di list
✅ Detail lengkap dengan timestamp
✅ Warna berbeda untuk REPORT dan ASK
✅ Auto-remove setelah dibalas
✅ Notifikasi jika masih ada report lain
✅ Semua tercatat di log file
✅ Maksimal 50 report aktif (mencegah spam)

### Breaking Changes:

❌ Command `/reply [playerid] [pesan]` dihapus
✅ Diganti dengan sistem dialog `/reports`

### Migration Guide:

Jika sebelumnya admin menggunakan:
```pawn
/reply 5 Terima kasih laporannya
```

Sekarang gunakan:
```pawn
/reports
// Pilih report dari dialog
// Klik "Balas"
// Ketik: Terima kasih laporannya
```

### Testing Checklist:

- [ ] Player bisa `/report` dengan sukses
- [ ] Player bisa `/ask` dengan sukses
- [ ] Admin menerima notifikasi
- [ ] `/reports` menampilkan list dengan benar
- [ ] Dialog detail menampilkan info lengkap
- [ ] Dialog reply berfungsi
- [ ] Balasan terkirim ke player
- [ ] Report terhapus setelah dibalas
- [ ] `/clearreports` berfungsi
- [ ] Log tersimpan dengan benar

### Known Issues:

- Report hilang saat server restart (by design)
- Player tidak bisa cek status report mereka (future feature)
- Maksimal 50 report aktif (bisa diubah di report_system.inc)

### Future Improvements:

- [ ] Command `/myreports` untuk player cek status
- [ ] Command `/cancelreport` untuk player
- [ ] Sistem priority (urgent/normal)
- [ ] Auto-assign report ke admin tertentu
- [ ] Database storage untuk persistent reports
- [ ] Notification sound untuk admin
- [ ] Report statistics untuk admin

---

**Version:** 1.0.3
**Date:** 2026-02-28
**Author:** Denmasmolano
