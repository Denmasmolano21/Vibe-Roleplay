# 🏗️ Vibe Roleplay - System Architecture

## 📐 System Overview

```
┌─────────────────────────────────────────────────────────────┐
│                    VIBE ROLEPLAY GAMEMODE                   │
│                         v1.0.3                              │
└─────────────────────────────────────────────────────────────┘
                              │
                              ▼
        ┌─────────────────────────────────────────┐
        │         INTERACTIVE SYSTEMS             │
        └─────────────────────────────────────────┘
                              │
        ┌─────────────────────┴─────────────────────┐
        │                                           │
        ▼                                           ▼
┌───────────────┐                          ┌───────────────┐
│  CORE SYSTEMS │                          │ PLAYER SYSTEMS│
└───────────────┘                          └───────────────┘
        │                                           │
        ├─ Auth System                             ├─ Vehicle System
        ├─ Database                                ├─ Inventory System
        ├─ Player Data                             ├─ Phone System
        ├─ Session                                 ├─ House System
        └─ Stats & HUD                             ├─ Business System
                                                   ├─ Job System
                                                   └─ Faction System
```

---

## 🔄 System Flow

### Player Login Flow
```
Player Connect
      │
      ▼
Name Validation ──[Invalid]──> Kick
      │
      │[Valid]
      ▼
Check Database
      │
      ├─[New]──> Register Dialog ──> Create Account ──> Login
      │
      └─[Exist]──> Login Dialog ──> Verify Password ──> Login
                                            │
                                            ▼
                                    Load Player Data
                                            │
                                            ▼
                                    Initialize Systems
                                            │
                                            ├─ Stats System
                                            ├─ Inventory System
                                            ├─ Phone System
                                            ├─ Vehicle System
                                            └─ Spawn Player
```

### Command Flow
```
Player Types Command (e.g., /v)
      │
      ▼
Command Guard Check
      │
      ├─[Not Logged In]──> Error Message
      │
      └─[Logged In]
            │
            ▼
      Show Dialog Menu
            │
            ▼
      Player Selects Option
            │
            ▼
      Dialog Response Handler
            │
            ├─ Execute Action
            ├─ Update Data
            ├─ Send Feedback
            └─ Show Next Dialog (if needed)
```

---

## 📦 Module Structure

### Vehicle System
```
Vehicle System
├── vehicle_data.inc
│   ├── Vehicle Data Structure
│   ├── Vehicle Iterator
│   └── Helper Functions
│
└── vehicle_core.inc
    ├── Vehicle Spawn/Destroy
    ├── Vehicle Save/Load
    ├── Engine/Lights/Lock
    ├── Fuel System
    └── Commands
        └── cmd_vehicle.inc
            ├── /v (Main Menu)
            ├── /engine
            ├── /lights
            ├── /lock
            └── /park
```

### Inventory System
```
Inventory System
└── inventory.inc
    ├── Item Data Structure
    ├── Inventory Slots (20)
    ├── Item Functions
    │   ├── Add Item
    │   ├── Remove Item
    │   ├── Use Item
    │   └── Has Item
    │
    └── Commands
        └── cmd_inventory.inc
            ├── /inv (Main Menu)
            ├── /giveitem
            └── /dropitem
```

### Phone System
```
Phone System
└── phone.inc
    ├── Phone Data Structure
    ├── Contact Management
    ├── SMS System
    ├── Call System
    │   ├── Phone_Call()
    │   ├── Phone_Hangup()
    │   └── Phone_SendSMS()
    │
    └── Commands
        └── cmd_phone.inc
            ├── /phone (Main Menu)
            ├── /call
            ├── /pickup
            ├── /hangup
            └── /sms
```

### House System
```
House System
└── house.inc
    ├── House Data Structure
    ├── House Iterator
    ├── House Functions
    │   ├── House_Create()
    │   ├── House_Buy()
    │   ├── House_Sell()
    │   ├── House_Enter()
    │   └── House_Exit()
    │
    └── Commands
        └── cmd_house.inc
            ├── /house (Main Menu)
            └── /exit
```

### Business System
```
Business System
└── business.inc
    ├── Business Data Structure
    ├── Business Types
    ├── Business Functions
    │   ├── Business_Create()
    │   ├── Business_Buy()
    │   ├── Business_Sell()
    │   └── Business_ShowMenu()
    │
    └── Commands
        └── cmd_business.inc
            └── /business (Main Menu)
```

### Job System
```
Job System
└── job.inc
    ├── Job Data Structure
    ├── Job Types (8 jobs)
    ├── Job Functions
    │   ├── Job_Accept()
    │   ├── Job_Quit()
    │   └── Job_ShowMenu()
    │
    └── Commands
        └── cmd_job.inc
            ├── /job (Main Menu)
            ├── /duty
            └── /quitjob
```

### Faction System
```
Faction System
└── faction.inc
    ├── Faction Data Structure
    ├── Faction Types
    ├── Faction Functions
    │   ├── Faction_Create()
    │   ├── Faction_Invite()
    │   └── Faction_ShowMenu()
    │
    └── Commands
        └── cmd_faction.inc
            ├── /faction (Main Menu)
            ├── /f (Chat)
            └── /finvite
```

---

## 🎯 Dialog System Architecture

### Dialog Handler Flow
```
OnDialogResponse
      │
      ▼
Switch (dialogid)
      │
      ├─ DIALOG_VEHICLE_MENU ──> Handle Vehicle Options
      ├─ DIALOG_INVENTORY_MAIN ──> Handle Inventory Options
      ├─ DIALOG_PHONE_MAIN ──> Handle Phone Options
      ├─ DIALOG_HOUSE_MENU ──> Handle House Options
      ├─ DIALOG_BUSINESS_MENU ──> Handle Business Options
      ├─ DIALOG_JOB_MENU ──> Handle Job Options
      └─ DIALOG_FACTION_MENU ──> Handle Faction Options
```

### Dialog ID Ranges
```
100-199: Auth & Core Dialogs
200-299: Help & Info Dialogs
300-399: Admin Dialogs
400-449: Vehicle Dialogs
450-499: Inventory Dialogs
500-549: Phone Dialogs
550-599: House Dialogs
600-649: Business Dialogs
650-699: Job Dialogs
700-749: Faction Dialogs
```

---

## 💾 Data Structure

### Player Data
```
PlayerData[playerid]
├── Account Info
│   ├── pID
│   ├── pPassword
│   ├── pLoggedIn
│   └── pRegistering
│
├── Character Info
│   ├── pLevel
│   ├── pMoney
│   ├── pSkin
│   └── pAdminLevel
│
├── Stats
│   ├── pHunger
│   ├── pThirst
│   └── pHealth
│
├── Position
│   ├── pPosX, pPosY, pPosZ
│   ├── pPosA
│   ├── pInterior
│   └── pVirtualWorld
│
└── Systems
    ├── PlayerJob[playerid]
    ├── PlayerFaction[playerid]
    ├── PlayerPhoneNumber[playerid]
    ├── PlayerInventory[playerid][]
    └── PlayerVehicleID[playerid]
```

### Vehicle Data
```
VehicleData[dataid]
├── vID (Database ID)
├── vModel
├── vOwnerID
├── vOwnerName
├── vSpawnX, vSpawnY, vSpawnZ, vSpawnA
├── vColor1, vColor2
├── vFuel
├── vHealth
├── vLocked
├── vEngine
├── vLights
└── vSpawned
```

### House Data
```
HouseData[houseid]
├── hID
├── hOwnerID
├── hOwnerName
├── hEntranceX, hEntranceY, hEntranceZ
├── hExitX, hExitY, hExitZ
├── hInterior
├── hVirtualWorld
├── hPrice
├── hLocked
├── hForSale
├── hPickupID
└── hLabel
```

---

## 🔌 Integration Points

### Database Integration
```
MySQL Database
├── players (Account data)
├── vehicles (Vehicle data)
├── houses (House data)
├── businesses (Business data)
├── factions (Faction data)
└── inventory (Inventory data)
```

### System Dependencies
```
Core Systems
      │
      ├─> Auth System ──> All Player Systems
      ├─> Database ──> All Data Systems
      ├─> Player Data ──> All Systems
      └─> Stats System ──> Inventory, Job
```

---

## 🎨 UI/UX Design Pattern

### Menu Structure
```
Main Menu
├── Header (System Name)
├── Info Section
│   ├── Current Status
│   └── Quick Info
│
├── Options List
│   ├── Option 1 [Tab] Description
│   ├── Option 2 [Tab] Description
│   └── Option N [Tab] Description
│
└── Buttons
    ├── "Pilih" (Select)
    └── "Tutup" (Close)
```

### Color Scheme
```
{FFFFFF} - White (Main text)
{00D4FF} - Light Blue (Headers, important info)
{00FF00} - Green (Success, positive)
{FF0000} - Red (Error, negative)
{FF6B00} - Orange (Admin)
{AFAFAF} - Gray (Secondary info)
```

---

## 🚀 Performance Optimization

### Iterator Usage
```
All major systems use YSI iterators:
- Iter:Vehicles
- Iter:Houses
- Iter:Businesses
- Iter:Factions
- Iter:Reports

Benefits:
✅ O(n) iteration instead of O(MAX)
✅ Memory efficient
✅ Fast lookups
```

### Timer Optimization
```
Timers:
├── VehicleFuelTimer (1000ms)
├── StatsDecayTimer (60000ms)
└── SessionTimer (300000ms)

All use YSI timers for better performance
```

---

## 📊 System Statistics

### Code Metrics
```
Total Systems: 7
Total Modules: 13
Total Commands: 30+
Total Dialogs: 50+
Total Functions: 100+
Lines of Code: 2500+
```

### Resource Usage
```
Memory:
- Player Data: ~2KB per player
- Vehicle Data: ~500B per vehicle
- House Data: ~300B per house
- Inventory: ~400B per player

Timers:
- 3 global timers
- Dynamic timers per player (death, etc)
```

---

## 🔐 Security Features

### Input Validation
```
All user inputs are validated:
✅ Command guards (GUARD_READY, GUARD_ADMIN)
✅ sscanf parameter validation
✅ Range checks (IDs, amounts)
✅ Permission checks
✅ State checks (logged in, in vehicle, etc)
```

### Data Protection
```
✅ Password hashing (bcrypt)
✅ SQL injection prevention (mysql_format)
✅ XSS prevention (dialog text escaping)
✅ Admin logging
```

---

## 🎯 Future Expansion

### Planned Features
```
Phase 2:
├── House Storage System
├── Business Product Management
├── Job Missions
├── Faction Territories
└── Advanced Phone Features

Phase 3:
├── Banking System
├── ATM System
├── Loan System
├── Insurance System
└── Achievement System
```

---

**Architecture designed for scalability and maintainability! 🏗️**

