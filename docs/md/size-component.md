# Joylink + Ali-smartliving

## Development environment

开发板：[ESP8266-DevKitC](https://www.espressif.com/sites/default/files/documentation/ESP8266-DevKitC_getting_started_guide__EN.pdf)

ESP8266_RTOS_SDK 版本： (master) commit_ID: 7f99618

## Total sizes:

DRAM .data size:    7672 bytes
DRAM .bss  size:     22448 bytes
Used static DRAM: 30120 bytes (  68184 available, 30.6% used)
Used static IRAM:   27614 bytes (  21538 available, 56.2% used)
Flash code:              740138 bytes
Flash rodata:           152640 bytes
Total image size: ~ 928064 bytes (.bin may be padded larger)

## Per-archive contributions to ELF file:
|             Archive File | DRAM |.data & .bss | IRAM | Flash | code & rodata | Total |
|--|--|--|--|--|--|--|
|             libiot_sdk.a |  689 |  2261 |     0 | 117409 | 34993 | 155352 |
|             libmbedtls.a |  100 |   112 |     0 | 123829 | 23729 | 147770 |
|             libjoylink.a | 3864 | 10845 |     0 |  67043 | 22273 | 104025 |
|                liblwip.a |   21 |     0 |  2507 |  75973 | 16078 |  94579 |
|                   libc.a |    4 |    20 |     0 |  72137 |  8216 |  80377 |
|            libnet80211.a |   70 |  1993 |    40 |  53464 |  4692 |  60259 |
|      libwpa_supplicant.a |    8 |   816 |     0 |  51411 |  2636 |  54871 |
|                 libphy.a |   47 |   290 |  2417 |  39872 |  2252 |  44878 |
|                  libpp.a |  387 |  3140 | 12765 |  16520 |  2906 |  35718 |
|                 libgcc.a |    0 |    37 |  2194 |  11656 |  2396 |  16283 |
|             libesp8266.a |   18 |   530 |   342 |  10589 |  4195 |  15674 |
|            libfreertos.a |  540 |  1262 |  3293 |   8861 |  1132 |  15088 |
|           libnvs_flash.a |    0 |    32 |     0 |  10402 |  2441 |  12875 |
|      libjoylink_extern.a | 1480 |    13 |     0 |   6845 |  4375 |  12713 |
|      liblinkkit_handle.a |   12 |   204 |     0 |   9437 |  2665 |  12318 |
| libesp-ali-smartliving.a |    0 |    21 |     0 |   8262 |  2783 |  11066 |
|              libstdc++.a |   24 |    72 |     0 |   5834 |  3919 |   9849 |
|                 libvfs.a |  264 |    48 |     0 |   7716 |   739 |   8767 |
|                libjson.a |   12 |     8 |     0 |   5773 |   618 |   6411 |
|             libesp-tls.a |    0 |     4 |     0 |   3873 |  1589 |   5466 |
|           libspi_flash.a |   24 |     9 |  1663 |   3045 |   224 |   4965 |
|           libesp_event.a |    4 |    13 |     0 |   3485 |   937 |   4439 |
|       libtcpip_adapter.a |    4 |   145 |     0 |   3735 |   343 |   4227 |
|             libpthread.a |    0 |    16 |     0 |   3065 |   596 |   3677 |
|                libcore.a |    0 |     0 |  1401 |   1998 |   202 |   3601 |
|          libesp_common.a |    0 |     0 |     0 |     49 |  3243 |   3292 |
|         libesp-joylink.a |    0 |     0 |     0 |   2388 |   752 |   3140 |
|          libapp_update.a |    0 |    72 |     0 |   1789 |   986 |   2847 |
|                libmain.a |    0 |     0 |     0 |   1716 |  1072 |   2788 |
|              libnewlib.a |    0 |   264 |     0 |   1971 |    53 |   2288 |
|  libbootloader_support.a |    0 |     0 |     0 |   1365 |   820 |   2185 |
|                libheap.a |    0 |    52 |   573 |    540 |     0 |   1165 |
|            libconn_mgr.a |    0 |     1 |     0 |    417 |   346 |    764 |
|         libesp_ringbuf.a |    0 |     0 |     0 |    691 |     0 |    691 |
|                 liblog.a |   70 |    20 |   110 |    314 |     0 |    514 |
|                 librtc.a |    0 |     0 |     0 |    288 |     0 |    288 |
|                 libhal.a |    0 |     0 |    37 |      0 |     0 |     37 |
|              libespnow.a |    0 |     0 |     0 |      0 |     0 |      0 |
|         libhttp_parser.a |    0 |     0 |     0 |      0 |     0 |      0 |

# Joylink

## Development environment

开发板：[ESP8266-DevKitC](https://www.espressif.com/sites/default/files/documentation/ESP8266-DevKitC_getting_started_guide__EN.pdf)

ESP8266_RTOS_SDK 版本： (master) commit_ID : 7f99618

Joylink 版本：(master) commit_ID : 53d7304

## Total sizes:

DRAM .data size:    6968 bytes
DRAM .bss  size:     19856 bytes
Used static DRAM: 26824 bytes (  71480 available, 27.3% used)
Used static IRAM:   27462 bytes (  21690 available, 55.9% used)
Flash code:              592950 bytes
Flash rodata:           110436 bytes
Total image size: ~ 737816 bytes (.bin may be padded larger)

## Per-archive contributions to ELF file:
|             Archive File | DRAM |.data & .bss | IRAM | Flash | code & rodata | Total |
|--|--|--|--|--|--|--|
|            libmbedtls.a |  100 |   112 |     0 | 121257 | 23729 | 145198 |
|            libjoylink.a | 3864 | 10845 |     0 |  67163 | 22277 | 104149 |
|               liblwip.a |   21 |     0 |  2507 |  75925 | 16078 |  94531 |
|                  libc.a |    4 |    20 |     0 |  71484 |  8210 |  79718 |
|           libnet80211.a |   70 |  1993 |    40 |  52691 |  4692 |  59486 |
|     libwpa_supplicant.a |    8 |   816 |     0 |  50307 |  2636 |  53767 |
|                libphy.a |   47 |   290 |  2425 |  39924 |  2252 |  44938 |
|                 libpp.a |  387 |  3140 | 12765 |  16536 |  2906 |  35734 |
|                libgcc.a |    0 |    37 |  2171 |  11636 |  2396 |  16240 |
|            libesp8266.a |   18 |   530 |   342 |  10578 |  4195 |  15663 |
|           libfreertos.a |  540 |  1262 |  3293 |   8777 |  1132 |  15004 |
|     libjoylink_extern.a | 1480 |    13 |     0 |   6861 |  4375 |  12729 |
|          libnvs_flash.a |    0 |    32 |     0 |  10200 |  2441 |  12673 |
|             libstdc++.a |   24 |    72 |     0 |   5738 |  3919 |   9753 |
|                libvfs.a |  264 |    48 |     0 |   7716 |   739 |   8767 |
|               libjson.a |   12 |     8 |     0 |   5789 |   618 |   6427 |
|            libesp-tls.a |    0 |     4 |     0 |   3667 |  1543 |   5214 |
|          libspi_flash.a |   24 |     9 |  1663 |   2750 |   183 |   4629 |
|          libesp_event.a |    4 |    13 |     0 |   3485 |   937 |   4439 |
|      libtcpip_adapter.a |    4 |   145 |     0 |   3659 |   343 |   4151 |
|         libesp_common.a |    0 |     0 |     0 |     49 |  3243 |   3292 |
|            libpthread.a |    0 |    16 |     0 |   2673 |   549 |   3238 |
|               libcore.a |    0 |     0 |  1267 |   1630 |   202 |   3099 |
|        libesp-joylink.a |    0 |     0 |     0 |   2336 |   752 |   3088 |
|             libnewlib.a |    0 |   264 |     0 |   1906 |    53 |   2223 |
|               libmain.a |    0 |     0 |     0 |    853 |   425 |   1278 |
|               libheap.a |    0 |    52 |   573 |    540 |     0 |   1165 |
|        libesp_ringbuf.a |    0 |     0 |     0 |    691 |     0 |    691 |
|           libconn_mgr.a |    0 |     0 |     0 |    264 |   277 |    541 |
|                liblog.a |   70 |    20 |   110 |    314 |     0 |    514 |
|libesp-ali-smartliving.a |    0 |     1 |     0 |    137 |   371 |    509 |
|                librtc.a |    0 |     0 |     0 |    288 |     0 |    288 |
|         libapp_update.a |    0 |     0 |     0 |      0 |   256 |    256 |
|                libhal.a |    0 |     0 |    37 |      0 |     0 |     37 |
| libbootloader_support.a |    0 |     0 |     0 |      0 |     0 |      0 |
|             libespnow.a |    0 |     0 |     0 |      0 |     0 |      0 |
|        libhttp_parser.a |    0 |     0 |     0 |      0 |     0 |      0 |

# Ali-smartliving

## Development environment

开发板：[ESP8266-DevKitC](https://www.espressif.com/sites/default/files/documentation/ESP8266-DevKitC_getting_started_guide__EN.pdf)

ESP8266_RTOS_SDK 版本： (master) commit_ID : 7f99618

Ali-smartliving 版本：(master) commit_ID : 4a750a5

## Total sizes:

DRAM .data size:    2384 bytes
DRAM .bss  size:     12240 bytes
Used static DRAM: 14624 bytes (  83680 available, 14.9% used)
Used static IRAM:   27614 bytes (  21538 available, 56.2% used)
Flash code:              678426 bytes
Flash rodata:           130272 bytes
Total image size: ~ 838696 bytes (.bin may be padded larger)

## Per-archive contributions to ELF file:
|             Archive File | DRAM |.data & .bss | IRAM | Flash | code & rodata | Total |
|--|--|--|--|--|--|--|
|            libiot_sdk.a | 755 | 2856 |     0 | 141567 | 40539 | 185717 |
|            libmbedtls.a | 100 |  112 |     0 | 122290 | 23729 | 146231 |
|               liblwip.a |  21 |    0 |  2507 |  73926 | 15764 |  92218 |
|                  libc.a |   4 |   20 |     0 |  71101 |  6530 |  77655 |
|           libnet80211.a |  70 | 1993 |    40 |  54166 |  4692 |  60961 |
|     libwpa_supplicant.a |   8 |  816 |     0 |  50727 |  2636 |  54187 |
|                libphy.a |  47 |  290 |  2417 |  39916 |  2252 |  44922 |
|                 libpp.a | 387 | 3141 | 12765 |  17109 |  2906 |  36308 |
|                libgcc.a |   0 |   37 |  2194 |  11672 |  2396 |  16299 |
|            libesp8266.a |  18 |  530 |   342 |  10601 |  4195 |  15686 |
|           libfreertos.a | 540 | 1262 |  3293 |   8861 |  1132 |  15088 |
|          libnvs_flash.a |   0 |   32 |     0 |  10378 |  2441 |  12851 |
|libesp-ali-smartliving.a |   0 |   25 |     0 |   9392 |  3331 |  12748 |
|     liblinkkit_handle.a |  12 |  204 |     0 |   9457 |  2665 |  12338 |
|             libstdc++.a |  24 |   72 |     0 |   5738 |  3919 |   9753 |
|                libvfs.a | 264 |   48 |     0 |   7716 |   739 |   8767 |
|            libesp-tls.a |   0 |    4 |     0 |   3768 |  1589 |   5361 |
|          libspi_flash.a |  24 |    9 |  1663 |   3045 |   224 |   4965 |
|          libesp_event.a |   4 |   13 |     0 |   3485 |   937 |   4439 |
|      libtcpip_adapter.a |   4 |  145 |     0 |   3679 |   343 |   4171 |
|            libpthread.a |   0 |   16 |     0 |   3013 |   596 |   3625 |
|               libcore.a |   0 |    0 |  1401 |   1998 |   202 |   3601 |
|         libesp_common.a |   0 |    0 |     0 |     49 |  3243 |   3292 |
|         libapp_update.a |   0 |   72 |     0 |   1785 |   986 |   2843 |
|             libnewlib.a |   0 |  264 |     0 |   1963 |    53 |   2280 |
| libbootloader_support.a |   0 |    0 |     0 |   1357 |   820 |   2177 |
|               libmain.a |   0 |    0 |     0 |    986 |   765 |   1751 |
|               libheap.a |   0 |   52 |   573 |    540 |     0 |   1165 |
|             libespnow.a |   0 |   56 |     0 |    410 |   439 |    905 |
|           libconn_mgr.a |   0 |    1 |     0 |    417 |   346 |    764 |
|        libesp_ringbuf.a |   0 |    0 |     0 |    691 |     0 |    691 |
|                liblog.a |  70 |   20 |   110 |    314 |     0 |    514 |
|                librtc.a |   0 |    0 |     0 |    288 |     0 |    288 |
|                libhal.a |   0 |    0 |    37 |      0 |     0 |     37 |
|        libhttp_parser.a |   0 |    0 |     0 |      0 |     0 |      0 |
