# Vibe Roleplay - SA-MP Gamemode

Gamemode Roleplay untuk SA-MP 0.3.7 dengan sistem autentikasi, stats (hunger/thirst), dan HUD.

## Fitur

### Sistem Autentikasi
- Register dengan bcrypt password hashing
- Login dengan validasi password
- Validasi nama roleplay (Format: Nama_Belakang)
- Anti brute-force (3x percobaan login)

### Sistem Stats
- Hunger system (berkurang 2 per menit)
- Thirst system (berkurang 3 per menit)
- HP drain saat hunger/thirst habis
- HUD textdraw untuk menampilkan stats

### Sistem Session
- Auto-save data pemain setiap 5 menit
- Playtime tracking
- Session management

### Sistem Spawn & Death
- Death timer (15 detik sebelum respawn)
- Hospital spawn dengan biaya perawatan
- Respawn dengan HP 50%

### Commands

#### Player Commands
- `/help` - Daftar command
- `/stats` - Lihat statistik pemain
- `/mypos` - Lihat posisi sekarang
- `/eat` - Makan (testing)
- `/drink` - Minum (testing)

#### Admin Commands
- `/sethunger [playerid] [amount]` - Set hunger pemain
- `/setthirst [playerid] [amount]` - Set thirst pemain
- `/givemoney [playerid] [amount]` - Beri uang ke pemain

## Struktur Folder

```
gamemodes/
├── gamemode.pwn              # Entry point
├── config/
│   ├── server_config.inc     # Konfigurasi server
│   ├── dialog_ids.inc        # Dialog IDs
│   └── colors.inc            # Definisi warna
├── core/
│   ├── player_data.inc       # Struktur data pemain
│   ├── player_state.inc      # State machine pemain
│   └── database.inc          # Koneksi database
├── utils/
│   ├── name_validator.inc    # Validasi nama RP
│   ├── messages.inc          # Fungsi pesan
│   └── command_guard.inc     # Macro validasi command
├── modules/
│   ├── auth/
│   │   ├── auth.inc          # Sistem autentikasi
│   │   └── auth_callbacks.inc # Callbacks auth
│   ├── session/
│   │   └── session.inc       # Session manager
│   ├── stats/
│   │   ├── stats.inc         # Sistem stats
│   │   └── stats_hud.inc     # HUD textdraws
│   └── spawn/
│       └── spawn.inc         # Sistem spawn/death
└── commands/
    └── cmd_general.inc       # Commands umum
```

## Database Schema

```sql
CREATE TABLE `players` (
    `id`            INT(11)         NOT NULL AUTO_INCREMENT,
    `username`      VARCHAR(24)     NOT NULL,
    `password`      VARCHAR(65)     NOT NULL,
    `admin_level`   INT(2)          NOT NULL DEFAULT '0',
    `skin`          INT(5)          NOT NULL DEFAULT '299',
    `money`         INT(11)         NOT NULL DEFAULT '0',
    `level`         INT(5)          NOT NULL DEFAULT '1',
    `hunger`        INT(3)          NOT NULL DEFAULT '100',
    `thirst`        INT(3)          NOT NULL DEFAULT '100',
    `playtime`      INT(11)         NOT NULL DEFAULT '0',
    `pos_x`         FLOAT           NOT NULL DEFAULT '1481.053',
    `pos_y`         FLOAT           NOT NULL DEFAULT '-1770.616',
    `pos_z`         FLOAT           NOT NULL DEFAULT '18.795',
    `pos_a`         FLOAT           NOT NULL DEFAULT '0.0',
    `interior`      INT(3)          NOT NULL DEFAULT '0',
    `virtual_world` INT(5)          NOT NULL DEFAULT '0',
    `created_at`    DATETIME        NOT NULL DEFAULT CURRENT_TIMESTAMP,
    `last_login`    DATETIME        NULL DEFAULT NULL,
    PRIMARY KEY (`id`),
    UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
```

## Konfigurasi

Edit `gamemodes/config/server_config.inc`:

```pawn
#define MYSQL_HOST              "127.0.0.1"
#define MYSQL_USER              "root"
#define MYSQL_PASS              ""
#define MYSQL_DB                "vrp"
```

## Include yang Diperlukan

- YSI v05.10.0006
- textdraw-streamer v2.0.3
- Pawn.CMD 3.4.0
- Streamer Plugin v2.9.6
- sscanf plugin v2.13.8
- MySQL R41-4
- samp_bcrypt v0.4.1
- CrashDetect v4.22
- Pawn.Regex v1.2.3

## Cara Compile

1. Buka `gamemodes/gamemode.pwn` di Pawno
2. Klik Compile atau tekan F5
3. Copy `gamemodes/gamemode.amx` ke folder `gamemodes/`
4. Jalankan server

## Changelog

Lihat [CHANGELOG.md](CHANGELOG.md) untuk daftar perubahan.

## Credits

- Author: Denmasmolano
- Version: 1.0.2
