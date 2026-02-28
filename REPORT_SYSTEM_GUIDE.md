# Report & Ask System - Panduan Lengkap

## Untuk Player

### Cara Melaporkan Masalah
```
/report [laporan anda]
```

**Contoh:**
```
/report Ada player yang cheating di ID 5
/report Bug di sistem spawn, saya spawn di laut
```

**Hasil:**
- Anda akan mendapat konfirmasi dengan ID report (contoh: #3)
- Admin online akan menerima notifikasi
- Jika tidak ada admin, report tersimpan untuk nanti

### Cara Bertanya ke Admin
```
/ask [pertanyaan anda]
```

**Contoh:**
```
/ask Bagaimana cara membeli rumah?
/ask Apakah boleh parkir kendaraan di sini?
```

**Hasil:**
- Anda akan mendapat konfirmasi dengan ID ask (contoh: #7)
- Admin online akan menerima notifikasi
- Tunggu balasan dari admin

---

## Untuk Admin

### Step 1: Menerima Notifikasi
Saat player menggunakan `/report` atau `/ask`, admin akan menerima:
```
[REPORT #3] John_Doe (ID: 5): Ada player yang cheating di ID 5
Gunakan /reports untuk melihat dan membalas.
```

atau

```
[ASK #7] Jane_Smith (ID: 12): Bagaimana cara membeli rumah?
Gunakan /reports untuk melihat dan membalas.
```

### Step 2: Melihat List Report/Ask
Ketik command:
```
/reports
```

**Dialog akan muncul dengan format:**
```
┌─────────────────────────────────────────────────┐
│  Vibe Roleplay - Reports & Asks (5)            │
├─────────────────────────────────────────────────┤
│ ID    Type      Player         Preview         │
├─────────────────────────────────────────────────┤
│ #3    REPORT    John_Doe       Ada player ya...│
│ #7    ASK       Jane_Smith     Bagaimana car...│
│ #12   REPORT    Mike_Johnson   Bug di sistem...│
│ #15   ASK       Sarah_Lee      Apakah boleh ...│
│ #18   REPORT    Tom_Brown      Lag parah di ...│
└─────────────────────────────────────────────────┘
   [Lihat]                              [Tutup]
```

**Keterangan Warna:**
- REPORT = Merah (masalah/keluhan)
- ASK = Biru (pertanyaan)

### Step 3: Melihat Detail Report
Pilih salah satu report, dialog detail akan muncul:

```
┌─────────────────────────────────────────────────┐
│  REPORT #3                                      │
├─────────────────────────────────────────────────┤
│ Dari          John_Doe (ID: 5)                 │
│ Kategori      REPORT                            │
│ Waktu         2 menit 15 detik lalu             │
│ Pesan         Ada player yang cheating di ID 5 │
│               menggunakan aimbot dan fly hack   │
└─────────────────────────────────────────────────┘
   [Balas]                            [Kembali]
```

### Step 4: Membalas Report
Klik "Balas", dialog input akan muncul:

```
┌─────────────────────────────────────────────────┐
│  Balas ke John_Doe                              │
├─────────────────────────────────────────────────┤
│  Ketik balasan kamu untuk player ini:           │
│                                                  │
│  [_________________________________]             │
│                                                  │
└─────────────────────────────────────────────────┘
   [Kirim]                             [Batal]
```

**Contoh balasan:**
```
Terima kasih laporannya, saya akan cek player tersebut
```

### Step 5: Hasil
- Player akan menerima pesan:
  ```
  [ADMIN REPLY] Admin_Name: Terima kasih laporannya, saya akan cek player tersebut
  ```
- Report otomatis terhapus dari list
- Admin mendapat konfirmasi:
  ```
  [SUCCESS] Balasan terkirim ke John_Doe: Terima kasih laporannya...
  [INFO] Masih ada 4 report/ask lainnya. Gunakan /reports
  ```

---

## Command Tambahan Admin

### Hapus Semua Report
```
/clearreports
```
Menghapus semua report/ask yang aktif (gunakan dengan hati-hati)

### Chat Admin
```
/a [pesan]
```
Chat khusus admin, hanya admin yang bisa lihat

---

## Tips untuk Admin

1. **Prioritas**: Balas REPORT terlebih dahulu (masalah lebih urgent)
2. **Cepat**: Usahakan balas dalam 5 menit
3. **Jelas**: Berikan jawaban yang jelas dan membantu
4. **Follow Up**: Jika perlu tindakan lebih lanjut, lakukan segera
5. **Log**: Semua balasan tercatat di admin_logs.txt

## Tips untuk Player

1. **Jelas**: Jelaskan masalah dengan detail
2. **Sabar**: Tunggu admin membalas
3. **Sopan**: Gunakan bahasa yang sopan
4. **Relevan**: Jangan spam report/ask
5. **ID**: Catat ID report/ask yang diberikan

---

## Sistem Penyimpanan

### Report/Ask tersimpan di:
- **Memory**: Maksimal 50 report/ask aktif
- **Log File**: `scriptfiles/report_logs.txt`
- **Admin Log**: `scriptfiles/admin_logs.txt`

### Auto-Remove:
- Report dihapus setelah admin balas
- Report dihapus saat server restart
- Admin bisa hapus manual dengan `/clearreports`

---

## Troubleshooting

**Q: Report saya tidak terkirim?**
A: Sistem mungkin penuh (max 50). Admin akan clear report lama.

**Q: Admin tidak balas?**
A: Mungkin tidak ada admin online. Report tersimpan dan akan dibalas nanti.

**Q: Bagaimana cara cek report saya?**
A: Saat ini belum ada command untuk player cek report. Tunggu balasan admin.

**Q: Bisa cancel report?**
A: Belum ada fitur cancel. Hubungi admin jika ingin cancel.
