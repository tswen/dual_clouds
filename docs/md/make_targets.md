# Make targets

| Commands                       | Help (en)                                                    | Help (zh_CN)                                                 |
| ------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| make menuconfig                | Configure IDF project                                        |                                                              |
| make defconfig                 | Set defaults for all new configuration options               | 恢复默认配置                                                 |
| make all                       | Build app, bootloader, partition table                       |                                                              |
| make flash                     | Flash app, bootloader, partition table to a chip             |                                                              |
| make clean                     | Remove all build output                                      |                                                              |
| make size                      | Display the static memory footprint of the app               | 显示应用程序的静态内存占用量                                 |
| make size-components           | Print per-component size information                         |                                                              |
| make size-files                | Print per-source-file size information                       |                                                              |
| make size-symbols              | Per symbol memory footprint. Requires COMPONENT=             | 每个 symbol 的内存占用量                                     |
| make erase_flash               | Erase entire flash contents                                  | 擦除整个 Flash 内容                                          |
| make erase_otadata             | Erase ota_data partition; First bootable partition (factory or OTAx) will be used on next boot. | 擦除 otadata 分区； 第一个可启动分区（factory 或OTAx）将在下次启动时使用 |
| make monitor                   | Run idf_monitor tool to monitor serial output from app       |                                                              |
| make simple_monitor            | Monitor serial output on terminal console                    |                                                              |
| make list-components           | List all components in the project                           | 列出项目中的所有组件                                         |
| make app-flash                 | Flash just the app                                           | 仅下载应用程序                                               |
| make app-clean                 | Clean just the app                                           | 仅清除应用程序                                               |
| make print_flash_cmd           | Print the arguments for esptool when flash                   | 刷新时打印 esptool 的参数                                    |
| make check_python_dependencies | Check that the required python packages are installed        | 检查是否已安装所需的 python 软件包                           |



