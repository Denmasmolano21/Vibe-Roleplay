# 🎮 Vibe Roleplay - Interactive System Guide

## 📋 Daftar Isi
1. [Vehicle System](#vehicle-system)
2. [Inventory System](#inventory-system)
3. [Phone System](#phone-system)
4. [House System](#house-system)
5. [Business System](#business-system)
6. [Job System](#job-system)
7. [Faction System](#faction-system)

---

## 🚗 Vehicle System

### Command Utama
- `/v` atau `/vehicle` - Buka vehicle menu (user-friendly interface)

### Menu Options
1. **My Vehicles** - Lihat semua kendaraan yang kamu miliki
2. **Engine** - Nyalakan/matikan mesin kendaraan
3. **Lights** - Nyalakan/matikan lampu kendaraan
4. **Lock/Unlock** - Kunci/buka kendaraan
5. **Park** - Parkir kendaraan di posisi saat ini
6. **Refuel** - Isi bensin kendaraan
7. **Trunk** - Akses bagasi kendaraan
8. **Hood** - Buka kap mesin

### Command Alternatif
- `/engine` - Toggle mesin
- `/lights` - Toggle lampu
- `/lock` - Toggle kunci
- `/park` - Parkir kendaraan
- `/myvehicles` - Lihat daftar kendaraan

### Fitur
- ✅ Sistem bensin otomatis
- ✅ Kunci kendaraan
- ✅ Parkir permanen
- ✅ Spawn/despawn kendaraan
- ✅ Fuel consumption saat mesin nyala

---

## 🎒 Inventory System

### Command Utama
- `/inv`, `/inventory`, atau `/i` - Buka inventory menu

### Menu Options
- Klik item untuk menggunakan
- Lihat semua item yang kamu miliki
- Jumlah item per slot

### Item Types
1. **Food** - Menambah hunger
   - Burger (+50 hunger)
   - Pizza (+75 hunger)
   - Hotdog (+30 hunger)

2. **Drink** - Menambah thirst
   - Water Bottle (+40 thirst)
   - Soda (+25 thirst)
   - Energy Drink (+50 thirst)

3. **Tools**
   - Rope
   - Lockpick
   - Medkit

4. **Phone** - Akses phone system

### Command Tambahan
- `/giveitem [playerid] [itemid] [amount]` - Berikan item ke player
- `/dropitem [itemid] [amount]` - Buang item

### Fitur
- ✅ 20 slot inventory
- ✅ Stackable items
- ✅ Use item langsung dari menu
- ✅ Give/drop items
- ✅ Auto-save inventory

---

## 📱 Phone System

### Command Utama
- `/phone` atau `/p` - Buka phone menu

### Menu Options
1. **Contacts** - Lihat dan kelola kontak
2. **Call** - Telepon seseorang
3. **SMS** - Kirim pesan
4. **SMS History** - Lihat riwayat SMS
5. **Add Contact** - Tambah kontak baru
6. **Settings** - Pengaturan phone

### Command Alternatif
- `/call [nomor]` - Telepon langsung
- `/pickup` - Angkat telepon
- `/hangup` atau `/h` - Tutup telepon
- `/sms [nomor] [pesan]` - Kirim SMS langsung

### Fitur
- ✅ Sistem nomor telepon unik
- ✅ Call system dengan pickup/hangup
- ✅ SMS system dengan history
- ✅ Contact management
- ✅ Roleplay actions (angkat phone, tutup phone)

---

## 🏠 House System

### Command Utama
- `/house` - Buka house menu (saat dekat rumah)

### Menu Options (For Sale)
1. **Buy House** - Beli rumah
2. **View Interior** - Lihat interior

### Menu Options (Owner)
1. **Enter** - Masuk rumah
2. **Lock/Unlock** - Kunci/buka rumah
3. **Sell House** - Jual rumah (50% dari harga beli)
4. **Upgrade** - Upgrade rumah
5. **Storage** - Akses storage rumah

### Command Tambahan
- `/exit` - Keluar dari rumah

### Fitur
- ✅ Buy/sell house system
- ✅ Lock system
- ✅ Interior system
- ✅ Virtual world per house
- ✅ 3D label dan pickup
- ✅ Storage system (coming soon)

---

## 🏢 Business System

### Command Utama
- `/business` atau `/biz` - Buka business menu (saat dekat bisnis)

### Business Types
1. **24/7 Store** - Toko serba ada
2. **Restaurant** - Restoran
3. **Gas Station** - SPBU
4. **Clothing Store** - Toko pakaian
5. **Gun Shop** - Toko senjata

### Menu Options (For Sale)
1. **Buy Business** - Beli bisnis
2. **Enter** - Masuk bisnis

### Menu Options (Owner)
1. **Enter** - Masuk bisnis
2. **Withdraw** - Ambil uang dari safe
3. **Sell Business** - Jual bisnis
4. **Manage** - Kelola bisnis

### Fitur
- ✅ Buy/sell business
- ✅ Safe system untuk income
- ✅ Multiple business types
- ✅ Employee system (coming soon)
- ✅ Product management (coming soon)

---

## 💼 Job System

### Command Utama
- `/job` - Buka job menu

### Available Jobs
1. **Trucker** - Antar barang ($500/job, Level 1)
2. **Taxi Driver** - Antar penumpang ($300/job, Level 1)
3. **Bus Driver** - Antar penumpang bus ($400/job, Level 2)
4. **Mechanic** - Perbaiki kendaraan ($350/job, Level 1)
5. **Medic** - Bantu pemain terluka ($450/job, Level 3)
6. **Pizza Boy** - Antar pizza ($250/job, Level 1)
7. **Street Sweeper** - Bersihkan jalanan ($200/job, Level 1)
8. **Miner** - Tambang material ($600/job, Level 5)

### Menu Options (No Job)
- Pilih job yang tersedia
- Lihat requirement level

### Menu Options (Has Job)
1. **Start Duty** - Mulai bekerja
2. **Stop Duty** - Berhenti bekerja
3. **Quit Job** - Resign dari pekerjaan
4. **Job Info** - Info detail pekerjaan

### Command Tambahan
- `/duty` - Toggle duty on/off
- `/quitjob` - Resign dari pekerjaan

### Fitur
- ✅ 8 jenis pekerjaan
- ✅ Level requirement
- ✅ Salary system
- ✅ Duty system
- ✅ Job locations dengan pickup
- ✅ Job missions (coming soon)

---

## 👥 Faction System

### Command Utama
- `/faction` - Buka faction menu

### Available Factions
1. **Los Santos Police Department** (LSPD)
2. **Los Santos Medical Center** (LSMC)
3. **San Andreas Government** (SAG)
4. **Gang/Mafia** (Custom)

### Menu Options (No Faction)
- Lihat faction yang tersedia
- Info untuk join faction

### Menu Options (Has Faction)
1. **Members** - Lihat anggota faction
2. **Invite** - Invite pemain ke faction
3. **Kick** - Kick anggota faction
4. **Ranks** - Kelola rank faction
5. **Leave** - Keluar dari faction

### Command Tambahan
- `/f [pesan]` - Chat faction
- `/finvite [playerid]` - Invite player (rank 5+)

### Fitur
- ✅ Multiple factions
- ✅ Rank system
- ✅ Faction chat
- ✅ Invite/kick system
- ✅ Faction HQ dengan pickup
- ✅ Faction colors
- ✅ Member management

---

## 🎯 Keunggulan Sistem

### User-Friendly Interface
- ✅ Semua sistem menggunakan dialog menu yang mudah
- ✅ Tidak perlu hafal command panjang
- ✅ Navigasi intuitif dengan tombol
- ✅ Info lengkap di setiap menu

### Konsistensi
- ✅ Semua sistem mengikuti pola yang sama
- ✅ Warna dan format seragam
- ✅ Command alternatif yang pendek
- ✅ Feedback message yang jelas

### Roleplay Friendly
- ✅ Action messages untuk interaksi
- ✅ Nearby messages untuk pemain sekitar
- ✅ Realistic features (fuel, hunger, thirst)
- ✅ Economy system terintegrasi

---

## 📝 Tips Penggunaan

1. **Gunakan command pendek** - `/v`, `/i`, `/p` lebih cepat dari command panjang
2. **Explore menu** - Semua fitur ada di menu, tidak perlu hafal command
3. **Baca info** - Setiap menu punya info lengkap tentang fitur
4. **Roleplay** - Gunakan action commands untuk roleplay yang lebih immersive
5. **Save progress** - Sistem auto-save, tapi pastikan logout dengan benar

---

## 🔄 Update & Development

Sistem ini terus dikembangkan dengan fitur-fitur baru:
- Storage system untuk house
- Business product management
- Job missions dan objectives
- Faction wars dan territories
- Advanced phone features
- Dan masih banyak lagi!

---

**Selamat bermain di Vibe Roleplay! 🎮**

