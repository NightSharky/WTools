# WMO Files (Main file)

### MVER
| Block | Size |
| ---- | ------ |
| MVER | 4 |
Structure:

    uint32 version;


***
### MOHD
| Block | Size |
| ----- | ---- |
| MOHD |   64  |
Structure:
    
    uint32 nMaterials;      // počet materiálů
    uint32 nGroups;
    uint32 nPortals;
    uint32 nLights;
    uint32 nModels;
    uint32 nDoodads;
    uint32 nSets;
    char ambient_color[4];  // last char 0xFF
    uint32 ID;
    float bounding_box[6];
    uint32 liquid_type;

***
### MOTX
| Block | Size |
| ---- | ------ |
| MOTX | variable |

Speaking about textures path. Obsahuje cestu k texturám. Oddělené znakem 0x00. Každá cesta je doplněná do počtu bytů dělitelného čtyřmi (zase znakem 0x00). Textura začíná 4 byty 0x00 (např.: 00 00 00 00 c e s t a 00 00 00)

| byte |  00  |  01  |  02  |  03  |  04  |  05  |  06  |  07  |  08  |  09  |  10  |  11  |
| ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| char |  00  |  00  |  00  |  00  |   c  |   e  |   s  |   t  |   a  |  00  |  00  |  00  |
| hex  |  00  |  00  |  00  |  00  |  63  |  65  |  73  |  74  |  61  |  00  |  00  |  00  |

***
### MOMT
| Block | Size |
| ---- | ------ |
| MOMT | nMaterials * 64  |
Structure:

    uint32 flags0;          // 0x04 - disable backface culling
    uint32 shader;          // is 0 ??
    uint32 blend_mode;      // is 0 ??
    uint32 texturePath0;    // offset into MOTX
    char color0[4];         // last one is 0xFF
    uint32 flags1;          // always 0
    uint32 texturePath1;    // offset to texture
    char color1[4];         // last char is 0xFF
    uint32 flags2;          // 0x0C valid dummy flag
    uint32 unknown[7];      // uint of float? who knows...

***
### MOGN
| Block | Size |
| ---- | ------ |
| MOGN |   |
Structure:

    unk

***
### MOGI
| Block | Size |
| ---- | ------ |
| MOGI |   |
Structure:

    unk

***
### MOSB
| Block | Size |
| ---- | ------ |
| MOSB |   |
Structure:

    unk

***
### MOPV
| Block | Size |
| ---- | ------ |
| MOPV |   |
Structure:

    unk

***
### MOPT
| Block | Size |
| ---- | ------ |
| MOPT |   |
Structure:

    unk

***
### MOPR
| Block | Size |
| ---- | ------ |
| MOPR |   |
Structure:

    unk

***
### MOVV
| Block | Size |
| ---- | ------ |
| MOVV |   |
Structure:

    unk

***
### MOVB
| Block | Size |
| ---- | ------ |
| MOVB |   |
Structure:

    unk

***
### MOLT
| Block | Size |
| ---- | ------ |
| MOLT |   |
Structure:

    unk

***
### MODS
| Block | Size |
| ---- | ------ |
| MODS | variable |

Its about doodad sets

Structure:

    unk

***
### MODN
| Block | Size |
| ---- | ------ |
| MODN |   |
Structure:

    unk

***
### MODD
| Block | Size |
| ---- | ------ |
| MODD |   |
Structure:

    unk

***
### MFOG
| Block | Size |
| ---- | ------ |
| MFOG |   |
Structure:

    unk

***