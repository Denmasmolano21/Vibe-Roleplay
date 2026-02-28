# 📖 Vibe Roleplay - Command Reference

## 🎮 Player Commands

### 🚗 Vehicle Commands
```
/v                  - Buka vehicle menu (RECOMMENDED)
/vehicle            - Alias untuk /v
/engine             - Toggle mesin kendaraan
/lights             - Toggle lampu kendaraan
/lock               - Kunci/buka kendaraan
/park               - Parkir kendaraan di posisi saat ini
/myvehicles         - Lihat daftar kendaraan kamu
```

### 🎒 Inventory Commands
```
/inv                - Buka inventory menu (RECOMMENDED)
/i                  - Alias untuk /inv
/inventory          - Alias untuk /inv
/giveitem [id] [itemid] [amount] - Berikan item ke player
/dropitem [itemid] [amount]      - Buang item
```

### 📱 Phone Commands
```
/phone              - Buka phone menu (RECOMMENDED)
/p                  - Alias untuk /phone
/call [nomor]       - Telepon seseorang
/pickup             - Angkat telepon
/hangup             - Tutup telepon
/h                  - Alias untuk /hangup
/sms [nomor] [msg]  - Kirim SMS
```

### 🏠 House Commands
```
/house              - Buka house menu (RECOMMENDED)
/exit               - Keluar dari rumah/interior
```

### 🏢 Business Commands
```
/business           - Buka business menu (RECOMMENDED)
/biz                - Alias untuk /business
```

### 💼 Job Commands
```
/job                - Buka job menu (RECOMMENDED)
/duty               - Toggle duty on/off
/quitjob            - Resign dari pekerjaan
```

### 👥 Faction Commands
```
/faction            - Buka faction menu (RECOMMENDED)
/f [pesan]          - Chat faction
/finvite [playerid] - Invite player ke faction (rank 5+)
```

### 📊 Stats & Info Commands
```
/stats              - Lihat statistik kamu
/mypos              - Lihat posisi kamu
/help               - Menu bantuan
```

### 🍔 Action Commands
```
/eat                - Makan (tambah hunger)
/drink              - Minum (tambah thirst)
```

### 📢 Report Commands
```
/report [laporan]   - Laporkan masalah ke admin
/ask [pertanyaan]   - Tanya admin
```

---

## 👮 Admin Commands

### 🎛️ Admin Panel
```
/admin              - Buka admin panel (RECOMMENDED)
/pm                 - Alias untuk /admin
/ahelp              - Menu bantuan admin
```

### 👥 Player Management
```
/kick [id] [alasan]     - Kick player
/ban [id] [alasan]      - Ban player
/freeze [id]            - Freeze player
/unfreeze [id]          - Unfreeze player
/slap [id] [alasan]     - Slap player
/setadmin [id] [level]  - Set admin level
```

### 📊 Player Stats
```
/sethealth [id] [amount]  - Set health player
/setarmour [id] [amount]  - Set armour player
/setskin [id] [skinid]    - Set skin player
/givemoney [id] [amount]  - Berikan uang
/setlevel [id] [level]    - Set level player
/sethunger [id] [amount]  - Set hunger player
/setthirst [id] [amount]  - Set thirst player
```

### 🔫 Weapon Management
```
/giveweapon [id] [weaponid] [ammo] - Berikan weapon
/resetweapon [id]                  - Reset weapon player
```

### 🚗 Vehicle Admin
```
/aveh [vehicleid] [color1] [color2] - Spawn kendaraan admin
/delveh                             - Hapus kendaraan
/repair                             - Repair kendaraan
/flip                               - Balikkan kendaraan
/respawnallveh                      - Respawn semua kendaraan
```

### 📍 Teleport Commands
```
/goto [playerid]        - Teleport ke player
/gethere [playerid]     - Teleport player ke kamu
/tp [x] [y] [z]         - Teleport ke koordinat
```

### 🔧 Server Management
```
/announce [pesan]       - Kirim announcement
/gmx                    - Restart gamemode
/reports                - Lihat semua report/ask
/clearreports           - Hapus semua report
```

### 💬 Admin Communication
```
/a [pesan]              - Chat admin
```

---

## 🎯 Quick Tips

### Untuk Player
1. **Gunakan menu** - Ketik `/v`, `/inv`, `/phone`, dll untuk akses menu lengkap
2. **Command pendek** - Gunakan alias seperti `/i`, `/p`, `/h` untuk lebih cepat
3. **Baca menu** - Semua info ada di menu, tidak perlu hafal command
4. **Roleplay** - Action commands otomatis kirim nearby message

### Untuk Admin
1. **Gunakan panel** - Ketik `/admin` untuk akses semua fitur admin
2. **Player list** - Pilih player dari list, tidak perlu ketik ID manual
3. **Log system** - Semua action admin ter-log otomatis
4. **Quick access** - Gunakan command langsung jika sudah hafal

---

## 📱 Item IDs (Inventory)

```
1  - Burger          (Food, +50 hunger)
2  - Pizza           (Food, +75 hunger)
3  - Hotdog          (Food, +30 hunger)
4  - Water Bottle    (Drink, +40 thirst)
5  - Soda            (Drink, +25 thirst)
6  - Energy Drink    (Drink, +50 thirst)
7  - Phone           (Phone)
8  - Rope            (Tool)
9  - Lockpick        (Tool)
10 - Medkit          (Misc)
```

---

## 💼 Job IDs

```
0 - None
1 - Trucker         ($500/job, Level 1)
2 - Taxi Driver     ($300/job, Level 1)
3 - Bus Driver      ($400/job, Level 2)
4 - Mechanic        ($350/job, Level 1)
5 - Medic           ($450/job, Level 3)
6 - Pizza Boy       ($250/job, Level 1)
7 - Street Sweeper  ($200/job, Level 1)
8 - Miner           ($600/job, Level 5)
```

---

## 🏢 Business Types

```
1 - 24/7 Store
2 - Restaurant
3 - Gas Station
4 - Clothing Store
5 - Gun Shop
```

---

## 👥 Faction Types

```
1 - Police (LSPD)
2 - Medic (LSMC)
3 - Government (SAG)
4 - Gang
5 - Mafia
```

---

## 🎨 Color Codes

```
{FFFFFF} - White
{00D4FF} - Light Blue (Primary)
{00FF00} - Green (Success)
{FF0000} - Red (Error)
{FF6B00} - Orange (Admin)
{AFAFAF} - Gray (Info)
{E74C3C} - Dark Red (Warning)
{3498DB} - Blue (Info)
{F39C12} - Yellow (Warning)
```

---

## 🔢 Common IDs

### Weapon IDs
```
22 - Colt 45
23 - Silenced Pistol
24 - Desert Eagle
25 - Shotgun
26 - Sawn-off Shotgun
27 - Combat Shotgun
28 - Micro SMG (Uzi)
29 - MP5
30 - AK-47
31 - M4
32 - Tec-9
33 - Country Rifle
34 - Sniper Rifle
```

### Skin IDs
```
0-311 - Valid skin IDs
Popular: 1, 2, 7, 14, 15, 23, 29, 30, 60, 98, 102, 105, 106, 107, 280, 281, 282, 283, 284, 285, 286, 287, 288
```

### Vehicle IDs
```
400-611 - Valid vehicle IDs
Popular:
400 - Landstalker
411 - Infernus
415 - Cheetah
429 - Banshee
451 - Turismo
506 - Super GT
560 - Sultan
562 - Elegy
```

---

## 📝 Notes

- **[id]** = Player ID (0-999)
- **[amount]** = Jumlah angka
- **[pesan]** = Text message
- **[nomor]** = Phone number
- **RECOMMENDED** = Command yang paling mudah digunakan

---

**Simpan file ini untuk referensi cepat! 📌**

