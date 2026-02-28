# Interactive Admin System - Panduan Lengkap

## Command Utama: `/admin`

Command `/admin` adalah menu interaktif lengkap untuk semua fungsi admin. Tidak perlu lagi mengetik command panjang dengan parameter!

## Struktur Menu

```
/admin
├── Player Management
│   ├── Pilih Player
│   └── Action Menu
│       ├── Kick (dengan input reason)
│       ├── Ban (dengan input reason)
│       ├── Freeze
│       ├── Unfreeze
│       ├── Slap (dengan input reason)
│       └── Set Admin (dengan input level)
│
├── Player Stats
│   ├── Pilih Player
│   └── Stats Menu
│       ├── Give Money (input amount)
│       ├── Set Level (input level)
│       ├── Set Hunger (input amount)
│       ├── Set Thirst (input amount)
│       ├── Set Health (input amount)
│       ├── Set Armour (input amount)
│       ├── Set Skin (input skin ID)
│       ├── Give Weapon (input weapon ID + ammo)
│       └── Reset Weapon
│
├── Vehicle Admin
│   ├── Spawn Vehicle (input vehicle ID + colors)
│   ├── Delete Vehicle
│   ├── Repair Vehicle
│   ├── Flip Vehicle
│   └── Respawn All Vehicles
│
├── Teleport
│   ├── Pilih Player
│   └── Teleport Menu
│       ├── Goto Player
│       ├── Get Player Here
│       └── Teleport to Coords (input X, Y, Z)
│
├── Reports
│   └── (Langsung ke /reports)
│
└── Server Management
    ├── Announce (input message)
    ├── Respawn All Vehicles
    ├── Clear Reports
    └── Restart GMX (dengan konfirmasi)
```

---

## Cara Penggunaan

### 1. Player Management

**Langkah-langkah:**
1. Ketik `/admin`
2. Pilih "Player Management"
3. Pilih player dari list
4. Pilih action yang diinginkan
5. Jika perlu input (kick/ban/slap), masukkan alasan
6. Konfirmasi

**Contoh: Kick Player**
```
/admin
→ Player Management
→ Pilih: John_Doe (ID: 5)
→ Pilih: Kick
→ Input: "Spam chat"
→ Player di-kick!
```

**Contoh: Freeze Player**
```
/admin
→ Player Management
→ Pilih: Jane_Smith (ID: 12)
→ Pilih: Freeze
→ Player langsung di-freeze!
```

**Contoh: Set Admin Level**
```
/admin
→ Player Management
→ Pilih: Mike_Johnson (ID: 8)
→ Pilih: Set Admin
→ Input: "3"
→ Player jadi admin level 3!
```

---

### 2. Player Stats

**Langkah-langkah:**
1. Ketik `/admin`
2. Pilih "Player Stats"
3. Pilih player dari list
4. Pilih stats yang ingin diubah
5. Masukkan nilai baru
6. Konfirmasi

**Contoh: Give Money**
```
/admin
→ Player Stats
→ Pilih: Sarah_Lee (ID: 15)
→ Pilih: Give Money
→ Input: "50000"
→ Player dapat $50,000!
```

**Contoh: Set Level**
```
/admin
→ Player Stats
→ Pilih: Tom_Brown (ID: 20)
→ Pilih: Set Level
→ Input: "25"
→ Player level jadi 25!
```

**Contoh: Give Weapon**
```
/admin
→ Player Stats
→ Pilih: Alex_White (ID: 7)
→ Pilih: Give Weapon
→ Input Weapon ID: "24" (Desert Eagle)
→ Input Ammo: "500"
→ Player dapat Deagle dengan 500 ammo!
```

**Contoh: Set Skin**
```
/admin
→ Player Stats
→ Pilih: Lisa_Green (ID: 18)
→ Pilih: Set Skin
→ Input: "141" (Skin wanita)
→ Skin player berubah!
```

---

### 3. Vehicle Admin

**Langkah-langkah:**
1. Ketik `/admin`
2. Pilih "Vehicle Admin"
3. Pilih action
4. Ikuti input yang diminta

**Contoh: Spawn Vehicle**
```
/admin
→ Vehicle Admin
→ Pilih: Spawn Vehicle
→ Input Vehicle ID: "411" (Infernus)
→ Input Color 1: "0" (Hitam)
→ Input Color 2: "0" (Hitam)
→ Infernus hitam spawn di depan kamu!
```

**Contoh: Repair Vehicle**
```
/admin
→ Vehicle Admin
→ Pilih: Repair Vehicle
→ Kendaraan langsung full HP!
```

**Contoh: Respawn All Vehicles**
```
/admin
→ Vehicle Admin
→ Pilih: Respawn All
→ Semua kendaraan kosong di-respawn!
```

---

### 4. Teleport

**Langkah-langkah:**
1. Ketik `/admin`
2. Pilih "Teleport"
3. Pilih player dari list
4. Pilih jenis teleport

**Contoh: Goto Player**
```
/admin
→ Teleport
→ Pilih: John_Doe (ID: 5)
→ Pilih: Goto Player
→ Kamu teleport ke John_Doe!
```

**Contoh: Get Player Here**
```
/admin
→ Teleport
→ Pilih: Jane_Smith (ID: 12)
→ Pilih: Get Player Here
→ Jane_Smith teleport ke kamu!
```

**Contoh: Teleport to Coords**
```
/admin
→ Teleport
→ Pilih: (player manapun)
→ Pilih: Teleport Coords
→ Input X: "1000.0"
→ Input Y: "-1000.0"
→ Input Z: "50.0"
→ Kamu teleport ke koordinat tersebut!
```

---

### 5. Reports

**Langkah-langkah:**
1. Ketik `/admin`
2. Pilih "Reports"
3. Langsung ke menu reports (sama seperti `/reports`)

Lihat [REPORT_SYSTEM_GUIDE.md](REPORT_SYSTEM_GUIDE.md) untuk detail lengkap.

---

### 6. Server Management

**Langkah-langkah:**
1. Ketik `/admin`
2. Pilih "Server"
3. Pilih action

**Contoh: Announce**
```
/admin
→ Server
→ Pilih: Announce
→ Input: "Server akan maintenance dalam 10 menit"
→ Semua player lihat announcement!
```

**Contoh: Restart GMX**
```
/admin
→ Server
→ Pilih: Restart GMX
→ Konfirmasi: Ya
→ Server restart dalam 5 detik!
```

---

## Keunggulan Sistem Interaktif

### ✅ Tidak Perlu Hafal Command
**Sebelum:**
```
/kick 5 spam chat
/ban 12 cheating
/givemoney 8 50000
/giveweapon 15 24 500
/aveh 411 0 0
```

**Sekarang:**
```
/admin
→ Pilih dari menu
→ Pilih player
→ Pilih action
→ Input jika perlu
→ Selesai!
```

### ✅ Tidak Perlu Ingat ID/Parameter
- List player otomatis muncul
- Tidak perlu ingat player ID
- Tidak perlu ingat vehicle ID
- Tidak perlu ingat weapon ID
- Semua ada di menu!

### ✅ Validasi Otomatis
- Input otomatis divalidasi
- Error message jelas
- Tidak bisa salah input

### ✅ User-Friendly
- Dialog interaktif
- Navigasi mudah
- Tombol "Kembali" di setiap menu
- Bisa cancel kapan saja

### ✅ Semua Tercatat
- Setiap action tercatat di log
- Admin name + timestamp
- Detail lengkap

---

## Command Lama Masih Bisa Digunakan

Semua command lama masih berfungsi untuk admin yang sudah terbiasa:

```
/kick [playerid] [reason]
/ban [playerid] [reason]
/freeze [playerid]
/givemoney [playerid] [amount]
/aveh [vehicleid] [color1] [color2]
/goto [playerid]
dll...
```

Tapi sekarang ada cara yang lebih mudah: `/admin`!

---

## Tips & Tricks

### 1. Shortcut untuk Reports
Langsung ketik `/reports` tanpa perlu buka `/admin` dulu.

### 2. Shortcut untuk Help
Langsung ketik `/ahelp` untuk bantuan command.

### 3. Admin Chat
Gunakan `/a [pesan]` untuk chat dengan admin lain.

### 4. Quick Actions
Untuk action yang sering digunakan, command lama lebih cepat:
- `/freeze 5` lebih cepat dari menu
- `/goto 12` lebih cepat dari menu

### 5. Complex Actions
Untuk action yang jarang atau butuh banyak input, gunakan menu:
- Give weapon (butuh weapon ID + ammo)
- Spawn vehicle (butuh vehicle ID + 2 colors)
- Set admin level (butuh konfirmasi)

---

## Troubleshooting

**Q: Menu tidak muncul?**
A: Pastikan kamu sudah login dan punya admin level minimal 1.

**Q: Player tidak ada di list?**
A: Player harus online dan sudah login.

**Q: Input tidak diterima?**
A: Pastikan format input benar (angka untuk amount, text untuk reason).

**Q: Action tidak jalan?**
A: Cek apakah player masih online dan cek log untuk error.

**Q: Ingin cancel di tengah jalan?**
A: Klik tombol "Batal" atau "Kembali" di dialog.

---

## Perbandingan: Command vs Menu

| Fitur | Command Lama | Menu Interaktif |
|-------|--------------|-----------------|
| Kecepatan | ⚡ Cepat (jika hafal) | 🐢 Agak lambat |
| Kemudahan | 😰 Susah (harus hafal) | 😊 Mudah (tinggal pilih) |
| Error | ❌ Sering salah input | ✅ Jarang error |
| Learning Curve | 📚 Tinggi | 📖 Rendah |
| Untuk Pemula | ❌ Tidak cocok | ✅ Sangat cocok |
| Untuk Expert | ✅ Cocok | ⚠️ Opsional |

**Rekomendasi:**
- Admin baru: Gunakan `/admin` (menu)
- Admin expert: Gunakan command langsung
- Situasi urgent: Command langsung
- Situasi santai: Menu interaktif

---

## Video Tutorial (Coming Soon)

1. Cara menggunakan `/admin` untuk pertama kali
2. Player Management dengan menu
3. Stats Management dengan menu
4. Vehicle Admin dengan menu
5. Teleport dengan menu
6. Server Management dengan menu

---

**Version:** 1.0.4
**Last Updated:** 2026-02-28
**Author:** Denmasmolano
