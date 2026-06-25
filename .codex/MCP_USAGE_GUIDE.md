@**MCP SAMPGAMMODE - SA-MP Pawn Development Tools**

## ?? Cara Penggunaan (Setup)

### 1?? Restart Codex CLI
Setelah config sudah diupdate, restart terminal/Codex CLI kamu agar MCP dimuat ulang:
```powershell
# Close terminal dan buka baru
codex
```

### 2?? Cara Pakai MCP ini di Direktori Lain
Untuk pakai MCP ini di project **lain**, ada 2 cara:

#### A. Setup MCP Global (Recommended untuk semua project)
1. Buat file `~/.codex/mcp.json` atau `C:/Users/guyub/.codex/mcp.json`
2. Tambahkan konfigurasi:
```json
{
  "mcpServers": {
    "samp-gammode-mcp": {
      "command": "node",
      "args": ["path/to/your/project/.codex/mcp/samp-gammode-mcp.js"],
      "cwd": "path/to/your/project"
    }
  }
}
```
3. Copy script `samp-gammode-mcp.js` ke setiap project yang kamu mau pake

#### B. Setup Per Project (Default)
Tinggal buat folder `.codex/mcp/` di setiap project SA-MP kamu, copy script MCP kesitu, dan update mcp.json sesuai path project tersebut.

Contoh untuk project lain:
```
D:/SA-MP/MyGame/.codex/mcp.json
```

---

## ?? Tools yang Tersedia

### ?? Compile & Build
| Tool | Deskripsi | Contoh Penggunaan |
|------|-----------|-------------------|
| `pawn_compile` | Compile .pwn ke .amx dengan mode debug/release | *"Compile gamemode dengan mode debug"* |
| `pawn_check_syntax` | Cek syntax cepat tanpa compile | *"cek syntax file scripts/test.pwn"* |
| `pawn_install_dependencies` | Install dependencies via sampctl/npm | *"install dependencies menggunakan sampctl"* |
| `pawn_clear_cache` | Hapus file .amx, logs, temp | *"clear cache type logs"* |

### ?? Server Control
| Tool | Deskripsi | Contoh Penggunaan |
|------|-----------|-------------------|
| `pawn_run_server` | Start SA-MP server | *"start server port 7777 maxplayers 64"* |
| `pawn_stop_server` | Stop server | *"stop server"* |
| `pawn_restart_server` | Restart server | *"restart server"* |
| `pawn_server_status` | Cek status server | *"apakah server masih jalan?"* |
| `pawn_start_fivem` | Alternative via sampctl/yampc | *"run server via sampctl"* |

### ?? Log Management
| Tool | Deskripsi | Contoh Penggunaan |
|------|-----------|-------------------|
| `pawn_get_log` | Baca log terakhir N baris | *"tampilkan log 50 baris terakhir"* |
| `pawn_filter_log` | Filter log by keyword/error | *"filter error dari log"* |

### ?? File Operations
| Tool | Deskripsi | Contoh Penggunaan |
|------|-----------|-------------------|
| `pawn_read_file` | Baca isi file dengan line range | *"baca main.pwn baris 10-50"* |
| `pawn_write_file` | Tulis/overwrite file | *"tulis content ke newfile.pwn"* |
| `pawn_copy_file` | Copy file ke tempat lain | *"copy main.pwn ke backup/"* |
| `pawn_list_dir` | List isi direktori | *"list file di gamemodes/"* |

### ?? Search & Analysis
| Tool | Deskripsi | Contoh Penggunaan |
|------|-----------|-------------------|
| `pawn_list_scripts` | List semua file .pwn/.inc | *"apa aja file .pwn di project ini?"* |
| `pawn_find_files` | Cari file by pattern/extension | *"cari semua file test.pwn"* |
| `pawn_find_include` | Cari #include usage | *"di mana include sscanf dipakai?"* |
| `pawn_find_function` | Cari function definition/usage | *"fungsi OnPlayerConnect dimana?"* |
| `pawn_extract_functions` | Extract semua public functions | *"list semua fungsi publik di main.pwn"* |
| `pawn_find_constants` | Cari semua constants/defines | *"daftar constants di constants.inc"* |
| `pawn_count_lines` | Hitung jumlah baris file | *"berapa baris main.pwn?"* |
| `pawn_get_dependencies` | Get semua required includes | *"apa aja dependency main.pwn?"* |
| `pawn_analysis_errors` | Analisis error di semua .pwn | *"scan error di seluruh project"* |

### ?? Backup & Version Control
| Tool | Deskripsi | Contoh Penggunaan |
|------|-----------|-------------------|
| `pawn_backup_gamemode` | Backup gamemode before changes | *"backup sebelum edit besar"* |
| `pawn_restore_gamemode` | Restore from backup | *"restore backup yesterday.pwn"* |
| `pawn_version_control` | Git operations | `"git status"` / `"commit message update"` |

### ?? Project Info
| Tool | Deskripsi | Contoh Penggunaan |
|------|-----------|-------------------|
| `pawn_project_info` | Info project overview | *"info project saya gimana?"* |
| `pawn_project_summary` | AI-friendly summary + recommendations | *"give me summary project ini"* |

---

## ?? Contoh Interaksi di Codex

### Scenario 1: Develop Baru
```
AI: Mari saya cek struktur project dulu...
User: List semua file .pwn
AI: Found 5 files: main.pwn, plugins.pwn, filterscripts/admin.pwn...
User: Baca main.pwn bagian include
AI: Showing first 50 lines with includes...
User: Compile dengan mode release
AI: Compiling now... Success! Output: gamemodes/main.amx
```

### Scenario 2: Debugging Error
```
User: Ada error di server, tolong cek log
AI: Mengambil 100 log terakhir...
Found ERROR: [18:32:15] Plugin 
sql.exe: Failed to load
User: Cari semua error di log
AI: Filtering errors only...
Found 3 errors: database connection failed, plugin not found...
```

### Scenario 3: Refactoring
```
User: Mau ganti nama fungsi OnPlayerConnect, toolong cari semua usage
AI: Searching for OnPlayerConnect usage...
Found 2 occurrences:
- main.pwn:123 (definition)
- admin.inc:456 (usage)
User: Backup dulu sebelum edit
AI: Creating backup at backups/main_2024-06-26.pwn
```

---

## ?? Tips Penggunaan Efisien

### ? Best Practices
1. **Selalu backup** sebelum perubahan besar ? `pawn_backup_gamemode`
2. **Check syntax** sebelum compile ? `pawn_check_syntax file.pwn`
3. **Gunakan log filter** saat debugging ? `pawn_filter_log errorOnly true`
4. **Scan dependencies** jika add include baru ? `pawn_get_dependencies`

### ? Quick Commands
```bash
# Cek apa aja masalahnya di project
pawn_analysis_errors strict true

# Lihat structure proyek
pawn_project_summary includeCode false

# Backup sebelum commit
pawn_backup_gamemode timestamp true
```

---

## ?? Update MCP Config untuk Project Lain

Jika pindah ke project lain (`D:/Projects/MySAProject/`):

```json
// D:/Projects/MySAProject/.codex/mcp.json
{
  "mcpServers": {
    "samp-gammode-mcp": {
      "command": "node",
      "args": ["D:/Projects/MySAProject/.codex/mcp/samp-gammode-mcp.js"],
      "cwd": "D:/Projects/MySAProject"
    }
  }
}
```

**Auto-detection**: MCP bisa auto-detect project root via environment variable `MCP_PROJECT_ROOT`.

---

## ?? Troubleshooting

| Masalah | Solusi |
|---------|--------|
| MCP tidak muncul di Codex | Restart terminal/Codex CLI |
| Error "Cannot read file" | Check path absolut vs relative |
| Compile gagal | PastikanPawn compiler ada di PATH |
| Server tidak start | Check `samp-server.exe` exists di cwd |

---

## ?? Fitur Advanced

### Auto Include Resolution
Script otomatis detect semua `#include` dalam chain dependencies!

### Smart Code Reading
`pawn_read_file` support line ranges untuk baca bagian tertentu saja (hemat context window!)

### Function Graph Analysis
`pawn_extract_functions` + `pawn_find_function` = understand call graph!

### Dependency Chain
`pawn_get_dependencies` recursive scan semua includes hingga depth penuh!

---

**Happy Coding! ????**

