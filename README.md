# Japanese
## e-Paperドライバ for ルネサスFSP
本ドライバはルネサスRA MCUでWaveshare e-Papaerモジュールを使用することを可能にします。

ルネサスRA MCUは、HALドライバやRTOS、各種ミドルウェアを含んだ[Flexible Software Package (FSP)](https://www.renesas.com/tw/ja/software-tool/flexible-software-package-fsp)と呼ぶソフトウェアを提供しています。本ドライバはこのFSP上で動作するように設計してあり、ユーザは特に手を加える必要なくe-Paperモジュールを動作させることができます。

本ドライバはWaveshareのgithubに公開されている[STM32用のe-Paperドライバ](https://github.com/waveshare/e-Paper)を改変して作成しています。APIの使用方法などの詳しい情報はWaveshareのHPなどをご参照ください。

また、本ドライバは、2.9インチのモジュールのみ、実機にて動作確認しています。他のモジュールはビルドがパスすることは確認していますが、実機で確認できていないことをご了承ください。

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
#### (3) モジュール設定
##### (a) モジュール追加
Stacksタブを開き、右上のNew Stackからr_spiモジュール/ドライバを追加します。
##### (b) クロック設定
クロック周波数を選択します。
(a)で追加したモジュールを選択し、プロパティでクロックを選択します。2.9インチのe-Paperモジュールの場合、[データシート](https://www.waveshare.com/wiki/File:2.9inch_e-Paper_Datasheet.pdf)によるとクロックサイクル時間は最小250nsにしなければならないので、4MHzを選択します。
##### (c) コールバック設定
SPIモジュールのコールバックを選択します。
本ドライバはコールバックを使用し、データ送信完了タイミングを取得します。コールバック関数名はデフォルトの「spi_callback」を設定してください。変更する場合はドライバのDEV_Config.cも合わせて変更してください。
#### (4) ドライバを適用
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

#### (5) メインルーチン作成
お好きなようにメイン処理プログラムを作成してください。

1点注意として、DEV_Module_Init関数を実行する前に、DEV_Config_Set関数をコールして、SPIモジュール構成とピン情報をドライバが使用できるようにしてください。設定方法はサンプルプロジェクトをご参照ください。
#### (6) ビルド&実行
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

# English
Comming soon.
