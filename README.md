# English
## e-Pape driver for Renesas FSP
This driver is possible to use Waveshare e-Paper module on Renesas RA MCU.

Renesas RA MCU provides software called [Flexible Software Package (FSP)](https://www.renesas.com/tw/ja/software-tool/flexible-software-package-fsp) that includes HAL driver, RTOS, and various middleware. This driver is designed to implemet on this FSP, and user can use the e-Paper module without any special modification.

This driver is created by modifying the [e-Paper driver for STM32](https://github.com/waveshare/e-Paper) published on Waveshare's github. For more information on how to use the API, please refer to the Waveshare website.

In addition, this driver has been confirmed to work only with 1.02 inch, 2.9 inch, 4.2 inch (black, white), and 4.2 inch (black, white and yellow) modules. In other modules, the author have confirmed that the build passes, but please note that the author have not confirmed the operation on the actual device.

Note: The author does not take any responsibility caused by this software, so please evaluate it carefully before using it in the system.

## Usage of this driver
Here are two ways to use the e-Paper driver.
1. Create a project from scratch.
2. Use sample project.

## 1. Create a project from scratch.
Create a project from scratch, and apply the driver.

#### (1) Create aproject
Create an FSP project. There is no particular specification.

Create a project by referring to "2.3.4 Create a New Project for Blinky" in the [FSP User's manual](https://www.renesas.com/tw/ja/document/man/renesas-flexible-software-package-fsp-v230-users-manual?language=en).
#### (2) Pin setting
Select the pin to connect the e-Paper in the FSP Configurator.
Pins used for SPI communication are selected from Peripherals on the Pins tab. In addition, GPIOs such as RST pin are selected from Ports.
#### (3) Select Heap size
Change the Heap size according to the size of the image cache of e-Paper to be used.
Select the BSP tab on the FSP Configurator and make changes in the Properties view.
#### (4) Module setting
##### (a) Add module
Open the Stacks tab and add the r_spi module / driver from the New Stack in the upper right.
##### (b) Clocks setting
Select the clock frequency.
Select the module added in (a) and select the clock in the properties. For a 2.9 inch e-Paper module, the [data sheet](https://www.waveshare.com/wiki/File:2.9inch_e-Paper_Datasheet.pdf) says that the clock cycle time should be a minimum of 250ns, so choose 4MHz.
##### (c) callback function setting
Select the SPI module callback.
This driver uses a callback to get the data transmission completion timing. Set the default "spi_callback" to the callback function name. If you want to change it, also change the driver in DEV_Config.c.
#### (5) Apply the driver
##### (a) Copy the driver into project
Copy the driver into your project.
Copy it directly under the project you want to apply by dragging and dropping.
##### (b) Enable build target
Just copying it may not be the target of the build, so enable it.
Right-click on the folder you want to enable and open its properties. Select C/C++ Build and chuck out Exclude Resource from build. Select "Apply and Close" to apply.
##### (c) Path setting
Add the driver path to your project.
Right-click on the project and open its properties. Open "Paths and Symbols" in "C/C++ General". Add the path to "GNU C" in "Includes" as follows. If you want to add it, chuck "Is a workspace path".

- /${ProjName}/e_paper_driver
- /${ProjName}/e_paper_driver/Config
- /${ProjName}/e_paper_driver/e-Paper
- /${ProjName}/e_paper_driver/Examples
- /${ProjName}/e_paper_driver/Fonts
- /${ProjName}/e_paper_driver/GUI

#### (6) Create main routine
Create the main processing program as you like.

One caveat is that you should call the DEV_Config_Set function before executing the DEV_Module_Init function to use the SPI module configuration and pin information available to the driver. Please refer to the sample project for the setting method.
#### (7) Build and Run
Build and run the project.

## 2. Use sample project.
The author provides a sample project.
For the import method, refer to "2.2.12 Importing an Existing Project into e2 studio" in the [FSP User's manual](https://www.renesas.com/tw/ja/document/man/renesas-flexible-software-package-fsp-v230-users-manual?language=en).
The environment and pin connection information are shown below.

#### Environmet used in the sample project
- e2studio 2021-01
- [FSP v2.3.0](https://github.com/renesas/fsp/releases/tag/v2.3.0)
- [EK-RA4W1](https://www.renesas.com/jp/ja/products/microcontrollers-microprocessors/ra-cortex-m-mcus/ek-ra4w1-ra4w1-mcu-group-evaluation-board)
- [2.9inch e-Paper module](https://www.waveshare.com/wiki/2.9inch_e-Paper_Module)

#### Pin connection
| RA4W1           | EK-RA4W1 |    | e-Paper module     |
---|---|---|---
| GPIO P103       | PMOD1-1  | -> | CS #low active     |
| SPI0 MOSI P101  | PMOD1-2  | -> | DIN                |
| SPI0 MISO P100  | PMOD1-3  | -- | (NC)               |
| SPI0 RSPCK P102 | PMOD1-4  | -> | CLK                |
| GPIO P107       | PMOD1-8  | -> | RST   #low active  |
| GPIO P204       | PMOD1-9  | -> | DC    #High: Data, Low: Command |
| GPIO P407       | PMOD1-10 | <- | BUSY  #high active |
| GND             | PMOD1-5  | -- | GND                |
| VCC 3.3V        | PMOD1-6  | -- | VCC                |


# Japanese
## e-Paperドライバ for ルネサスFSP
本ドライバはルネサスRA MCUでWaveshare e-Papaerモジュールを使用することを可能にします。

ルネサスRA MCUは、HALドライバやRTOS、各種ミドルウェアを含んだ[Flexible Software Package (FSP)](https://www.renesas.com/tw/ja/software-tool/flexible-software-package-fsp)と呼ぶソフトウェアを提供しています。本ドライバはこのFSP上で動作するように設計してあり、ユーザは特に手を加える必要なくe-Paperモジュールを動作させることができます。

本ドライバはWaveshareのgithubに公開されている[STM32用のe-Paperドライバ](https://github.com/waveshare/e-Paper)を改変して作成しています。APIの使用方法などの詳しい情報はWaveshareのHPなどをご参照ください。

また、本ドライバは、1.02インチ、2.9インチ、4.2インチ白黒、4.2インチ白黒黄のモジュールのみ、実機にて動作確認しています。他のモジュールはビルドがパスすることは確認していますが、実機では動作を確認できていないことをご了承ください。

※筆者は本ソフトウェアによって生じた責任は一切負いませんので、システムに組み込む際は十分に評価してご使用ください。

## 使用方法
e-Papaerドライバを使用する2つの方法を以下に示します。
1. 1からプロジェクトを生成
2. サンプルプロジェクトを使用

## 1. 1からプロジェクトを生成
プロジェクトを1から作成し、ドライバを適用します。

#### (1) プロジェクト生成
FSPのプロジェクトを作成します。特に指定はありません。
[FSP User's manual](https://www.renesas.com/tw/ja/document/man/renesas-flexible-software-package-fsp-v230-users-manual?language=en)の「2.3.4 Create a New Project for Blinky」などを参考にプロジェクトを作成してください。
#### (2) ピン設定
e-Paperを接続するピンをFSPコンフィグレータで選択します。
SPI通信で使用するピンはPinsタブのPeripheralsから追加します。その他、RSTピンなどのGPIOはPortsから追加します。
#### (3) Heapサイズ選択
使用するe-Paperのイメージキャッシュのサイズに合わせて、Heapサイズを変更してください。
FSPコンフィグレータのBSPタブを選択し、プロパティービューで変更します。
#### (4) モジュール設定
##### (a) モジュール追加
Stacksタブを開き、右上のNew Stackからr_spiモジュール/ドライバを追加します。
##### (b) クロック設定
クロック周波数を選択します。
(a)で追加したモジュールを選択し、プロパティでクロックを選択します。2.9インチのe-Paperモジュールの場合、[データシート](https://www.waveshare.com/wiki/File:2.9inch_e-Paper_Datasheet.pdf)によるとクロックサイクル時間は最小250nsにしなければならないので、4MHzを選択します。
##### (c) コールバック設定
SPIモジュールのコールバックを選択します。
本ドライバはコールバックを使用し、データ送信完了タイミングを取得します。コールバック関数名はデフォルトの「spi_callback」を設定してください。変更する場合はドライバのDEV_Config.cも合わせて変更してください。
#### (5) ドライバを適用
##### (a) ドライバをプロジェクトにコピー
ドライバをプロジェクト内にコピーします。
ドラッグ＆ドロップで適用したいプロジェクトの直下にコピーします。
##### (b) ビルド対象を有効化
コピーしただけではビルドの対象でない場合がありますので有効にします。
有効にしたいフォルダを右クリックし、プロパティを開きます。C/C++ Buildを選択し、Exclude Resource from buildをチャックアウトします。Apply and Closeを選択し、適用します。
##### (c) パス設定
ドライバのパスをプロジェクトに追加します。
プロジェクトを右クリックし、プロパティを開きます。C/C++ GeneralのPaths and Symbolsを開きます。IncludesのGNU Cに以下のようにパスを追加します。追加する場合は、Is a workspace pathをチャックしてください。

- /${ProjName}/e_paper_driver
- /${ProjName}/e_paper_driver/Config
- /${ProjName}/e_paper_driver/e-Paper
- /${ProjName}/e_paper_driver/Examples
- /${ProjName}/e_paper_driver/Fonts
- /${ProjName}/e_paper_driver/GUI

#### (6) メインルーチン作成
お好きなようにメイン処理プログラムを作成してください。

1点注意として、DEV_Module_Init関数を実行する前に、DEV_Config_Set関数をコールして、SPIモジュール構成とピン情報をドライバが使用できるようにしてください。設定方法はサンプルプロジェクトをご参照ください。
#### (7) ビルド&実行
ビルドして、実行します。

## 2. サンプルプロジェクト
サンプルプロジェクトを提供します。
インポート方法は[FSP User's manual](https://www.renesas.com/tw/ja/document/man/renesas-flexible-software-package-fsp-v230-users-manual?language=en)の「2.2.12 Importing an Existing Project into e2 studio」をご参照ください。
環境とピン接続情報を以下に示します。

#### サンプルプロジェクトで使用している環境
- e2studio 2021-01
- [FSP v2.3.0](https://github.com/renesas/fsp/releases/tag/v2.3.0)
- [EK-RA4W1](https://www.renesas.com/jp/ja/products/microcontrollers-microprocessors/ra-cortex-m-mcus/ek-ra4w1-ra4w1-mcu-group-evaluation-board)
- [2.9インチe-Paperモジュール](https://www.waveshare.com/wiki/2.9inch_e-Paper_Module)

#### ピン接続情報
| RA4W1           | EK-RA4W1 |    | e-Paper module     |
---|---|---|---
| GPIO P103       | PMOD1-1  | -> | CS #low active     |
| SPI0 MOSI P101  | PMOD1-2  | -> | DIN                |
| SPI0 MISO P100  | PMOD1-3  | -- | (NC)               |
| SPI0 RSPCK P102 | PMOD1-4  | -> | CLK                |
| GPIO P107       | PMOD1-8  | -> | RST   #low active  |
| GPIO P204       | PMOD1-9  | -> | DC    #High: Data, Low: Command |
| GPIO P407       | PMOD1-10 | <- | BUSY  #high active |
| GND             | PMOD1-5  | -- | GND                |
| VCC 3.3V        | PMOD1-6  | -- | VCC                |
