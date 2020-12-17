# Light Demo of Joylink

## 一、介绍

`light demo`为客户提供一种简易的智能灯解决方案，客户可根据自己的需要进行二次开发，实现更加更加丰富的控制操作。

## 二、解决方案部署

**1.参考 [README](../../README.md) 文档进行硬件准备、环境搭建、SDK 准备**

**2.烧录三元组信息**

- 可通过 `menuconfig` 录入`UUID`、`PRIVATE_KEY`、`DEVICE_MAC`等信息

**3.配置 `Light Demo`**

- ESP32 开发板：RGB 灯默认分别接在 `GPIO25`, `GPIO26`, `GPIO27` 
- ESP32S2 开发板：RGB 灯默认分别接在 `GPIO34`, `GPIO35`, `GPIO36` 
- ESP8266 开发板：RGB 灯默认分别接在 `GPIO4`, `GPIO5`, `GPIO15` 

>GPIO可通过menuconfig中`Joylink->light_red、light_green、light_blue`进行个性化配置

**4.编译`light_demo`并烧录运行**

对于 ESP32 平台，请输入如下命令进行编译烧录

```
cd examples/light_demo
idf.py build
idf.py -p /dev/ttyUSBx flash monitor
```

对于 ESP32S2 平台，请使用如下命令进行编译烧录

```
cd examples/light_demo
idf.py set-target esp32s2
idf.py build
idf.py -p /dev/ttyUSBx flash monitor
```

对于 ESP8266 平台，请使用如下命令进行编译烧录

```
cd examples/light_demo
make -j8 flash monitor
```

>ESP32 平台也可使用 make 指令，但在将来的 esp-idf 主要版本中，可能会删除对 GNU Make 构建系统的支持。

## 三、运行

* 扫描二维码

    <img src="../../docs/_picture/Demo二维码.jpg" width = "300" alt="i2c hardware" align=center />
    
* 配网界面

    <img src="../../docs/_picture/微联APP-配网界面.jpg" width = "300" alt="i2c hardware" align=center />
    
* 选择合适的 AP 进行配网（乐鑫设备仅支持 2.4G AP）

* 等待建立连接

    >若连接过程中 app 未发现设备的 softAP，则可根据提示进行手动连接至设备的 softAP
    
* 连接服务器成功后用户设备列表中会出现该智能灯设备


* 用户可通过点击开关以及氛围灯对智能灯设备进行控制

    > 开启设备显示白色灯光
    >
    > 开启氛围灯显示紫色灯光

## 四、二次开发

* 用户可通过修改 joylink_light.c 文件实现更加个性化的智能灯控制

