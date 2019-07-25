= Amazon Cognito 入門

== はじめに
現在のシステム開発、サービス開発プロジェクトは昔よりどんどん複雑化しています。
理由はいろいろとありますが、主にサービスのスマホ対応や競合他社との差別化等で
付加する機能が多くなってきていることが考えられます。
また、市場のブルーオーシャンをいかに早く獲得できるか、アイデアからサービスをリリースする速度が重要視されています。


一方でサービスの開発にかけられる期間は昔と比べて少なくなっています。
特にサービスの特徴である部分以外の開発には、コストも工数もあまりかけられません。
中でも、認証機能はどのサービスにもほぼ必須の機能ですが、
セキュリティ面や認証ロジックなど考慮すべき事がたくさんあり開発が複雑になってきています。


本章では、そのようなプロジェクト環境に置かれている方に向けて簡単に
バックエンドの認証システムを開発できる Amazon Cognito サービスを紹介していきます。


また、Cognito を簡単に利用できることを伝えるために React Native 用のチュートリアルを用意しています。
チュートリアルを進めるにあたり少しの React Native の知識があれば進めることができるようになっています。

== 開発環境の構築
本書では、開発環境に下記のミドルウェア、ライブラリを利用します。

 * React Native
 * npm
 * Expo
 * AWS Amplify フレームワーク

また、認証テスト用に下記のクラウドサービスを利用します。

 * Amazon Cognito

アプリの動作検証には下記のアプリを利用します。

 * Expo Client アプリ

本書を進めるにあたり必要な開発環境は次の通りです。

 * AWS アカウント
 * 統合開発環境(IDE) またはエディタ（著者は VS Code を利用しました。）
 * Mac or Windows（本章のテストアプリを作成する為の開発環境にOSの違いは特にございません。お好きなOSで開発環境を用意してください。）




=== Expo 開発環境の構築

==== Expo アカウントの作成
本書で利用する環境は、無料のオープンソースツールチェーンである Expo を利用します。
Expo は、Expo 社から提供されている React Native を javascript でラッピングした開発ツールです。
javascript と React Native を利用して、ネイティブの iOS 及び Android プロジェクトを開発することができます。
また、アンドロイド・iOS アプリで配布されている Expo Client アプリをインストールすることで、アプリをビルドをすることなく実機で動作確認を行うことができます。
Expo の公式ページにアクセスし、Expo プロジェクトを開始しましょう。

Expo 公式サイト： @<href>{https://expo.io}

まず、アカウントを作成します。このアカウントは後でアプリの実機確認をするためのユーザ認証で必要になりますので作りましょう。
「Create an account」（@<img>{first_page}）をクリックします。

//image[first_page][Expo 公式サイト：トップ画面][scale=0.70]{
//}

利用規約「Terms Of Service」とプライバシーポリシー「Privacy Policy」に同意する場合、「E-MAIL」、「USERNAME」、「PASSWORD」、「CONFIRM PASSWORD」を入力し最後に「Create your account」をクリックし、アカウントを作成します（@<img>{create_account}）。

//image[create_account][Expo 公式サイト：アカウント作成画面][scale=0.70]{
//}

アカウント作成が完了するとプロジェクトホーム画面へ自動で遷移します（@<img>{top_page}）。
アカウント作成時に登録した e-mail アドレスにアカウント検証用のメールが送付されているのでリンクをクリックし、アカウント作成を完全に完了させます。


//image[top_page][Expo 公式サイト：プロジェクトホーム画面][scale=1.00]{
//}

以上でアカウント作成が完了しました。

==== Expo のインストール
開発環境には React Native の開発環境が簡単に構築できる Expo cli を利用します。
Expo cli は、初期プロジェクトの展開、node サーバの起動、モバイルアプリの実機デバッグ用 QR コードの発行を行います。
モバイルアプリのビルドに Android Studio や Xcode は必要ありません。


では、まず Expo cli をインストールしましょう。
Expo cli は次の npm コマンドでインストールします。

//cmd{
$ npm install expo-cli --global
//}

次に、expo プロジェクトの作成を行います。任意のディレクトリで次のコマンドを
実行しプロジェクトを作成しましょう。

//cmd{
$ expo init my-new-project
//}

プロジェクトのテンプレートを利用するかを聞かれるので今回は blank (@<list>{template})を選択します。

//list[template][テンプレートの選択]{
? Choose a template:
> blank
  minimum dependencies to run and an empty root component 
  tabs
  several example screens and tabs using react-navigation
//}

プロジェクトフォルダに移動して expo サーバを起動させます。

//cmd{
$ cd my-new-project
$ expo start
//}

expo サーバが起動すると次のブラウザ（@<img>{expo_web}）が自動で開きます。
ブラウザ上に QR コードが表示されます。
開発したコードを実機で確認するためには、Android または iPhoneで QR コードを読み取ります。
QR コードは localhost、LAN、Expo 公式ホスティングサービスの 3 種類の QR コードが発行されるのでご利用の環境に合わせて適宜ご利用ください。
特に、無料で React Native のホスティングをしてくれるのは非常に便利です。会社の PC 端末とスマートフォンが LAN でアクセスできない環境の場合は重宝します。

//image[expo_web][Expo サーバ起動ブラウザ画面][scale=0.70]{
//}

サーバの環境は以上です。
次に実機でアプリを確認する場合に Expo Client アプリをインストールしていきます。

=== Expo Client アプリのインストール
Expo Client アプリをインストールします。
お手持ちの iOS または Android のアプリストアでインストールできます。

iOS：
@<href>{https://itunes.apple.com/app/apple-store/id982107779}

Android：
@<href>{https://play.google.com/store/apps/details?id=host.exp.exponent}

先ほどの QR コードを QR コードリーダで読み取ります。読み取ると Expo Client アプリが開き、アプリのビルドとダウンロードが自動で行われます（@<img>{initboundle}）。

//image[initboundle][左:Expo アプリビルド画面　右:expo アプリ初期画面][scale=0.60]{
//}

ビルドとダウンロードが完了すると画像のような初期プロジェクトのアプリ画面が出てきます（@<img>{initboundle}）。

以後は、ソースコードを変更し保存するだけでアプリの画面が自動で更新・反映されます。
以上が Expo アプリを使ったアプリの実機確認方法になります。
では、次の項から Amazon Cognito を解説します。

== Amazon Cognito の概要
===  なぜ認証機能のクラウドサービスを利用するのか
なぜわざわざ認証機能を自前で構築せずにクラウドサービスを利用するのでしょうか。
その背景には、サービスのマイクロサービス化にあります。


最近のサービス開発プロジェクトでは、スクラッチでバックエンドを開発することが稀になってきています。
PaaS 等のクラウドサービスの登場でサービスをマイクロサービスの組み合わせで作成することが多くなってきました。
サービスのコアではない部分は、既存のサービスを組み込むことで大幅に開発工数を削減することができます。
特に認証機能は作り込めば作り込むほどサービスの利益が上がるようなコア部分ではないにもかかわらず
ロジックが複雑な上、セキュリティを担保できるように開発しないといけません。
スピードが重要視されるプロジェクトでは、そこにかける工数も時間もありません。
そのような背景で、バックエンドの認証機能に外部のサービスを利用することが多くなっています。


本章ではクラウドの認証サービスである Amazon Cognito の使い方を紹介します。

=== Amazon Cognito について
Amazon Cognito とはウェブアプリケーションやモバイルアプリケーション、の認証とユーザ管理を提供しているサービスです。
認証画面の認証機能や API の認証、ユーザ管理などのユーザ認証系システムをサーバレスでセキュアに設定・管理できるサービスです。
ここでは、Amazon Cognito が提供している「ユーザプール」と「ID プール」についてチュートリアルとともに解説します。

=== Amazon Cognito の無料枠
Amazon Cognito サービスには無料利用枠があります。個人利用の場合無料枠で十分運用できるので是非活用しましょう。
無料枠の範囲は次のとおりです（@<img>{cost}）。（2019年 3月時点）@<fn>{cost}

//image[cost][Amazon Cognito 料金][scale=0.80]{
//}

//footnote[cost][Amazon Cognito 公式サイト：https://aws.amazon.com/jp/cognito/pricing/]


月間アクティブユーザ（MAU）が50,000 までは無料それ以降は MAU あたりの料金がかかります。
ここでの MAU は サインアップやサインイン、パスワードの再発行、アクセストークンの更新など Amazon Cognito の認証に関する処理が行われるごとに 1 MAU とカウントされます。


== Amazon Cognito の設定
Amazon Cognito の設定をします。ここでは AWS マネジメントコンソールで設定していきます。
ご自身の AWS アカウントを用意してサインインまで準備をしておいてください。


設定する内容は Cognito User Pool と Cognito ID Pool です。

=== Cognito User Pool とは
Cognito User Pool は Amazon Cognito のユーザアカウントデータが保存されているディレクトリです。
ユーザは Amazon Cognito を通じて User Pool に格納されているアカウントで認証してモバイルアプリにログインできます。
また、Google や Facebook など別のプロバイダー認証サービスから経由して User Pool にサインインすることもできます。

User Pool は次の機能を提供しています。

 * サインアップおよびサインインサービス
 * ユーザーがサインインするための組み込みのカスタマイズ可能なウェブ UI
 * Facebook、Google からのソーシャルサインイン
 * ユーザーディレクトリとユーザープロファイルの管理
 * 多要素認証 (MFA) などのセキュリティ機能、漏洩した認証情報のチェック、アカウントの乗っ取り保護、電話と E メールによる検証

また、Cognnito の認証後に発行される JWT@<fn>{jwt} を利用することで独自で作成した API へのアクセスを保護することができます。

//footnote[jwt][JWT（Json Web Token）とは、電子署名付きの トークンを Json 形式で保持したもの。改ざんができないような JSON。]

=== Cognito ID Pool とは
Cognito ID Pool は、認証ユーザーに対して別の AWS のサービスへのアクセスを許可する AWS 認証情報を提供することができます。
IAM のポリシーと組み合わせると認証済みユーザにしか実行できない API を作成することができます。

==={userpool} Cognito User Pool の設定
User Pool を設定していきましょう。チュートリアルでは簡単に説明するためほとんどの機能をデフォルトの設定で進めます。
プロダクションで利用する際はアプリのポリシーに従って適切な値で設定してください。

User Pool の名前を決めます。何でもいいですがここでは「test_cognito」とします（@<img>{name}）。
//image[name][User Pool 名の設定][scale=1.00]{
//}

サインインの属性を選択します（@<img>{zokusei}）。
属性ではサインインのためのユーザ名にどのような情報を利用するかを決めることができます。
任意のユーザIDや電話番号、メールアドレスなどをユーザ名として認証情報に利用することができます。
また、属性のエイリアスを設定することで複数の情報をユーザ名として利用することができます。

デフォルトのままで設定します。
//image[zokusei][属性の設定][scale=1.00]{
//}

次にポリシーを選択します（@<img>{policy}）。
パスワードの強度や管理者が作成したパスワードの有効期限が設定できます。
これらはあとからも変更することができます。

デフォルトのままで設定します。
//image[policy][ポリシーの設定][scale=1.00]{
//}

最後にアプリクライアントを設定します （@<img>{app_client}）。
アプリクライアントは User Pool にアクセスするための固有の ID になります。
この ID をアプリに登録することで、アプリ外から User Pool にアクセスされることを防ぐことができます。

「クライアントシークレットを生成のチェックボックス」を外して「アプリクライアントの作成」を押下します。
//image[app_client][アプリクライアントの設定][scale=1.00]{
//}

本書では上記設定で Cognito サービスを利用します。

他にも次のような設定項目があります。プロダクション環境に合わせて設定してください。

 * 多要素認証 (MFA)
//quote{
エンドユーザのセキュリティ強化のために多要素認証を設定することができます。
//}

 * メッセージのカスタマイズ
//quote{
確認コードのメール内容のカスタマイズや招待メールのカスタマイズを行うことができます。
//}
 * ユーザデバイスの認証情報記憶
//quote{
認証情報の記憶設定を「有効」、「無効」、「Opt In」から選択することができます。
//}

 * トリガーの設定
//quote{
認証前、認証後のカスタムイベントの作成をすることができます。
これにより認証前の不審なユーザの拒否設定や認証チャレンジレスポンスの設定などができます。
//}

確認画面で設定内容を確認します。問題なければプールの作成を押下して User Pool を作成します（@<img>{confirm}）。
//image[confirm][確認画面][scale=1.00]{
//}


==={idpool} Cognito ID Pool の設定
テスト用の ID Pool を設定していきましょう。
「新しい ID Pool の作成」を行います。ここでは「test_cognito」で進めます（@<img>{id}）。
「認証されていないID」にチェックを入れます。チェックを入れることでサインインフォームなどを通して認証されていないユーザに対しても API を実行できるようにします。
例えば「パスワードお忘れの方」などサインイン処理をしていないユーザに対して API を提供することができます。


「認証プロバイダー」では、パブリックプロバイダーからの認証を設定することができます。様々な外部プロバイダーと連携できるようになっています。
本書ではこの認証プロバイダーは利用しません。

//image[id][Cognito ID Pool の設定][scale=1.00]{
//}

設定が完了したら「プールの作成」を押下します。


次に、ロールの設定を行います。次の画面に自動で遷移されるので「詳細を表示」を押下してロールの設定を行います（@<img>{cognito_role_top}）。
//image[cognito_role_top][Cognito ID Pool の設定][scale=1.00]{
//}

詳細を表示するとロールの概要が表示されます（@<img>{cognito_role}）。

//image[cognito_role][Cognito ID Pool の設定][scale=1.00]{
//}


認証済みユーザに対して下記のようなポリシーがアタッチされています(@<list>{role})。
ここには、ユーザが認証済みの場合に操作できる AWS サービスを IAM ポリシーをアタッチすることができます。
認証済みユーザのみ S3 のバケットを操作したり、API　Gateway の API を実行するなど AWS サービスへの許可ポリシーを付与します。


ここでは、デフォルトのまま設定をします。

//list[role][Cognito_test_cognitoAuth_Role]{
{
  "Version": "2012-10-17",
  "Statement": [
    {
      "Effect": "Allow",
      "Action": [
        "mobileanalytics:PutEvents",
        "cognito-sync:*",
        "cognito-identity:*"
      ],
      "Resource": [
        "*"
      ]
    }
  ]
}
//}

以上が Cognito ID Pool の設定です。
これで Amazon Cognito を利用する準備が整いました。
次項ではアプリから Cognito を利用する方法を解説します。

== Amplify フレームワーク を利用した Cognito 認証アプリ
=== Amplify の概要
Amplify は バックエンドに AWS を使用したモバイルアプリおよびウェブアプリの作成、設定、実装を容易にする SDK です。
AWS サービスをバックエンドにした React Native や iOS、Android、Web アプリのフロントエンドとの結合に 
Amplify フレームワークと UI コンポーネントを使用して、次の機能をアプリケーションに統合することができます。

 *データ
 *認証
 *解析
 *API
 *ストレージ
 *プッシュ通知
 *ボット
 *AR/VR等

本章ではモバイルバックエンドとして Amazon Cognito を利用するので、 
Amplify の認証フレームワークをプロジェクトにインポートして Amazon Cognito を操作します。

=== Amplify のインストール
プロジェクトに Amplify をインストールします。
初期プロジェクトのフォルダ構成は次 (@<list>{srctree})のようになっています。

//list[srctree][my-new-project]{
App.js
app.json
assets
babel.config.js
node_modules
package.json
package-lock.json
//}

プロジェクトフォルダに移動して Amplify を npm コマンドでインストールします。
今回は、 amplify フレームワークと amplify の React Native 用 UI コンポーネントをインストールします。

//cmd{
$ npm install react-amplify
$ npm install aws-amplify-react-native
//}

Amazon Cognito サービスを SDK から利用するには先ほど作成した Cognito User Pool と Cognito ID Pool
の設定が必要になります。「aws-export.js」ファイルをプロジェクト直下に作成し次のような config の設定を行います（@<list>{aws-export}）。

//list[aws-export][aws-export.js]{
import Amplify from 'aws-amplify';

Amplify.configure({
  Auth: {
    // REQUIRED - Amazon Cognito Identity Pool ID
    identityPoolId: 'ap-northeast-1:xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxx',
    // REQUIRED - Amazon Cognito Region
    region: 'ap-northeast-1',
    // OPTIONAL - Amazon Cognito User Pool ID
    userPoolId: 'ap-northeast-1_xxxxxxxxxx',
    // OPTIONAL - Amazon Cognito Web Client ID
    userPoolWebClientId: 'xxxxxxxxxxxxxx',
  },
});
//}

「aws-amplify」は Javascript 用の Amplify フレームワークになります。
 @<hd>{userpool} と @<hd>{idpool} で作成したときに返却された値を「identityPoolId」、「region」、「userPoolId」、「userPoolWebClientId」に設定します。

完了したら「App.js」を開いて先ほど作成した設定ファイルを import します（@<list>{aws-config-import}）。

//list[aws-config-import][設定ファイルのインポート: app.js]{
import React from 'react';
import { StyleSheet, Text, View } from 'react-native';
/** AWS Amplify と Cognito config 情報をインポート  */
import Amplify from 'aws-amplify';
import config from './aws-export';

Amplify.configure(config);
----- 省略 -----

//}

=== 認証画面の作成
認証画面を作成します。認証画面は「aws-amplify-react-native」パッケージの UI コンポーネントを利用します。
UI コンポーネントを利用することで、下記の認証機能と画面を簡単に作成できます。

 * サインイン
 * サインアップ
 * パスワード再発行
 * サインアップ・パスワード再発行用コード送信

では、コードを記述していきます。記述すると言ってもとても簡単です。認証用のコンポーネントを配置するだけです。
次のように「App.js」のコードを修正します（@<list>{aws-amplify-react-native}）。

//list[aws-amplify-react-native][認証コンポーネントの配置: app.js]{
import React from 'react';
import { StyleSheet, Text, View } from 'react-native';
/** 認証用 UI コンポーネントをインポート */ 
import { withAuthenticator } from 'aws-amplify-react-native';

/** AWS Amplify と Cognito config 情報をインポート  */
import Amplify from 'aws-amplify';
import config from './aws-export';

Amplify.configure(config);

class App extends React.Component {   // <-- export default を削除
  render() {
    return (
      <View style={styles.container}>
        <Text>Open up App.js to start working on your app!</Text>
      </View>
    );
  }
}

export default withAuthenticator(App);  // <-- App コンポーネントの前に認証コンポーネントを呼び出す

const styles = StyleSheet.create({
----- 省略 -----

//}

では、作成したアプリをスマートフォンで確認しましょう。初期プロジェクトで発行した QR コードで開いたアプリがそのままの方は
ソースコードを 保存 するだけでホットリロードされて Expo アプリに反映されます。
もし Expo アプリを閉じてしまった方は再度 QR コードを読み取るとアプリのビルドが始まります。
サーバを停止したりエラーで止まってしまった場合はもう一度「expo start」コマンドを実行しサーバを立ち上げ直しましょう。


アプリ画面に次のような認証画面が出れば Cognito 認証アプリの完成です（@<img>{cognito-signin-frame}）。

//image[cognito-signin-frame][サインイン画面][scale=0.40]{
//}

たった数行のコードを書くだけでサインイン、サインアップ、パスワード再発行、サインアップ・パスワード再発行用コード送信の画面と機能を実装することができました。

試しに「Sign Up」をタップしてユーザを作成してみます。
登録したいユーザ名、パスワード、メールアドレス、電話番号を入力し 「SIGN UP」を押下します（@<img>{sinupconfirm}）。

//image[sinupconfirm][左:サインアップ画面　右:確認コード入力画面][scale=0.60]{
//}

登録したメールアドレスに認証コードが送付されるのでメールを確認し「Confirm Sign UP」画面にユーザ名と確認コードを入力します（@<img>{sinupconfirm}）。


最後に、「Confirm」ボタンを押下すると Cognito User Pool にユーザが登録されます。
AWS マネジメントコンソールにログインし Cognito User Pool を確認するとユーザが登録されていることが確認できます（@<img>{user-pool}）。

Cognito User Pool のマネジメントコンソールでは登録されているユーザ情報を閲覧できる他にもユーザの作成、ユーザの無効化、アカウントのステータス状況の確認、ユーザインポートなどが
GUI で操作できるようになっています。


//image[user-pool][Cognito User Pool の画面][scale=0.70]{
//}

=== 認証画面のカスタマイズ
「aws-amplify-react-native」の UI コンポーネントには HOC (@<fn>{hoc})が用意されています。
HOC を利用すると簡単に UI コンポーネントのカスタマイズができます。

ここでは日本語化とコンポーネントのカスタマイズ方法を紹介します。

//footnote[hoc][Higher-Order Component: 既存のコンポーネントに後から機能を追加したりカスタマイズしたりできるデザインパターン]

==== 日本語化の設定
既存の UI コンポーネントはデフォルトで英語になっているので日本語化のカスタマイズをします。
「App.js」に下記コードを追加します（@<list>{japanese}）。

//list[japanese][日本語化の設定]{
import React from 'react';
import { StyleSheet, Text, View } from 'react-native';
import { withAuthenticator } from 'aws-amplify-react-native'; 

/** AWS Amplify と Cognito config 情報をインポート  */
import Amplify from 'aws-amplify';
import config from './aws-export';

Amplify.configure(config);

/** 日本語化の設定 */
const dict = {
  'ja': {
    'Sign In Account': "サインイン",
    'Sign In': "サインイン",
    'Sign Out': "サインアウト",
    'Sign Up Account': "サインアップ",
    'Sign Up': "サインアップ",
    'Skip': "スキップする",
    'Submit': "保存",
    'Username': "ユーザー名",
    'Verify Contact': "確認",
    'Verify': "確認する"
   }
};

Amplify.I18n.setLanguage('ja');
Amplify.I18n.putVocabularies(dict);

class App extends React.Component {
------- 省略 ------
//}

英語の key と対応する日本語の Value を持った json 配列 「dict」変数を定義します。
json の key は認証画面に表示されている英語の文字列そのままが Key になっています。

言語に関するモジュールは「aws-amplify」に組み込まれている軽量の国際言語化モジュールである「I18n」関数を呼び出します。
「I18n.setLanguage」で言語設定を日本語にセットし「I18n.putVocabularies」の引数に json 配列を渡します。

以上が日本語化の設定です。



==== コンポーネントのカスタマイズ
サインイン画面やサインアップ画面の入力フォームの項目を追加したり、必要のないコンポーネントを削除したいときがあるかと思います。
そのような場合でも HOC を利用して既存コンポーネントを拡張した独自の認証コンポーネントを適応することができます。

次のコードは HOC を利用して既存コンポーネントを拡張したサンプルコードになります（@<list>{cognito-extend}）。
「withAuthenticator」の引数に認証画面で必要なコンポーネントを配列形式で列挙しています。
引数には既存の認証コンポーネントを拡張した独自のコンポーネントを渡すこともできます。
このコードの例では、既存の「SignIn」コンポーネントを拡張した独自の「MySignIn」コンポーネントを新たなサインイン画面のコンポーネントとして引数に渡しています。

//list[cognito-extend][拡張した認証コンポーネント]{
-------- 省略 -------
/** 認証に必要なコンポーネントをインポートする */
import { 
  withAuthenticator, 
  ConfirmSignIn, 
  VerifyContact, 
  SignUp, 
  ConfirmSignUp, 
  ForgotPassword, 
  RequireNewPassword 
} from 'aws-amplify-react-native';

-------- 省略 -------
class App extends React.Component {
  render() {
    return (
      <View style={styles.container}>
        <Text>Open up App.js to start working on your app!</Text>
      </View>
    );
  }
}

class MySignIn extends SignIn {
  render() {
    /** ここに独自でカスタマイズしたサインインコンポーネント */
  }
}

/** 認証機能に必要なコンポーネントを定義する */
export default withAuthenticator(App, false, [
  <MySignIn />,
  <ConfirmSignIn />,
  <VerifyContact />,
  <SignUp />,
  <ConfirmSignUp />,
  <ForgotPassword />,
  <RequireNewPassword />
]);

const styles = StyleSheet.create({
---------- 省略 ----------
//}


==== 独自のデザインと認証機能のロジックをカスタマイズしたい場合
「aws-amplify-react-native」の用意された UI コンポーネントと組み込まれた認証機能を使わずに独自で認証機能・画面を実装することもできます。
その場合は「aws-amplify-react-native」の UI コンポーネントを使わずに AWS Amplify Javascript @<fn>{amplify-api}を利用します。

//footnote[amplify-api][https://aws-amplify.github.io/docs/js/]

AWS Amplify Javascript は　Javascript から Amplify で提供されている AWS サービスの機能を呼び出せる API になります。
実は今までのサンプルでも密かにインポートしており、「aws-amplify」というモジュールが AWS Amplify Javascript の実態となります。
AWS Apmlify Javascript では Cognito 用の認証 API、 Authentication API も提供されています。
この API を利用すれば 「aws-amplify-react-native」を利用せずに UI 部分と 認証 API を切り離して開発することができます。

Amplify Javascript の Authentication API ドキュメントが非常にわかりやすく解説されているのでそちらのリンクを共有します。

Authentication API
@<href>{https://aws-amplify.github.io/docs/js/authentication}

ここまでが Amazon Cognito を用いたクライアント側のお話でした。
次項からはバックエンド側の Amazon Cognito SDK を用いた開発方法についてお話します。


== ステートレスなバックエンドサービスの認証情報管理
ステートフルなバックエンドサービスで作成したWebアプリケーションでは認証状態をセッション情報として持つことができます。
したがって、特に Cognito サービスを利用したからといって特別な認証管理を実装する必要はありません。

では、API のようなステートレスなバックエンドサービスを利用する場合は認証情報をどのように担保すればよいでしょうか。
ここではバックエンドに API を用いた場合のユーザの認証情報の管理方法について解説します。

=== API を用いた認証情報の管理について
API を利用したステートレスなシステムの場合、認証状態をセッションで持っておくことはできません。
したがって、モバイル（Web）アプリケーションが API をリクエストするときに認証情報をバックエンドに送らなければなりません。
認証情報を送ることができればバックエンドは正規のユーザが API をリクエストしたかの判断ができます。

Cognito User Pool はそのようなケースのために認証に成功するとレスポンスにユーザプールトークンを発行します。
API をリクエストする際にモバイルアプリケーションがユーザプールトークンをリクエストに添付することで、セキュアな API の実行を実現することができます。
また、「Amazon Cognito SDK」を利用しているプロジェクトではユーザプールトークン自体の管理をする必要はありません。
ユーザプールトークンの期限が切れている場合 SDK が自動で更新トークンを用いてユーザプールトークンを更新してくれます。
「aws-amplify」フレームワークも「Amazon Cognito SDK」が含まれているので React Native でトークンの更新処理を明示的に書く必要はありません。


では、そのユーザプールトークンからどのように正規なユーザかどうかを確認すれば良いでしょうか。
ユーザプールトークンは JWT の形で Base64 url 文字列暗号化された状態でユーザプールから返却されます。
トークンは次のように「.」区切りで構成されています（@<list>{jwt}）。

1. ヘッダー

2. ペイロード

3. 著名

//list[jwt][JWT の構成]{
1111111111.22222222222.333333333
//}

「ヘッダー」にはこの暗号化された JWT を復号化するための公開鍵のヒントが保存されています。
「ペイロード」には AWS 側の秘密鍵で暗号化されたユーザ情報が保存されています。

API を提供するバックエンドではこの JWT を復号化しなければいけません。
ただし API Gateway を利用する場合はこの JWT を利用したユーザの認証処理を省くことができます。
復号化はバックエンドで実装しなければいけません。復号化の手順は AWS 公式サイトに解説されています。
@<br>{}

@<href>{https://docs.aws.amazon.com/ja_jp/cognito/latest/developerguide/amazon-cognito-user-pools-using-tokens-verifying-a-jwt.html}
@<br>{}

ここではバックエンドに独自の API を利用する場合の JWT の復号化手順を説明します。

==== 1. JWT トークンのデコード
JWT のデコードは利用する言語によってライブラリが提供されています。
下記リンクを参考に言語に合わせたライブラリを利用するとデコードの処理を簡単に実装できます。

JWT トークンライブラリ一覧: @<href>{https://openid.net/developers/jwt/}

==== 2. JWK と JWT のヘッダーから公開鍵を作成
リモートにある JWK@<fn>{jwk} と 復号化した JWT のヘッダーに含まれている情報から公開鍵を作成します。
//footnote[jwk][JWK（JSON Web Key）とは、暗号鍵を表現するためのデータ構造。]

==== 3. 公開鍵を用いて JWT 著名の検証
JWT トークンライブラリに JWT 著名を検証する関数が含まれているのでそちらを用いて JWT の著名検証を行います。

==== 4. クレームの検証
復号化したペイロードに含まれる情報から下記の内容を検証します

 * 有効期限が切れていないか
 * User Pool で設定したアプリクライアント ID からのアクセスかどうか
 * User Pool ID が合致しているかどうか
 * API のリクエストユーザと JWT ペイロードに含まれているユーザが一致しているかどうか 

これらの手順を踏むことで API の実行ユーザが信頼できるかどうかが検証できます。
しかし、独自で API を実装する場合、実装するのは大変だと思います。
その場合は API Gateway の活用も考えましょう。
これらの処理を AWS 側で自動で処理してくれます。

以上がバックエンドに API を用いた場合のユーザの認証管理方法でした。

== まとめ
Amazon Cognito の活用方法について次のように解説してきました。

 * Amazon Cognito の設定
 * Amplify を利用した Cognito 認証アプリの作成
 * aws-amplify-react-native を用いた認証画面の作成
 * HOC を用いた認証画面のカスタマイズ
 * Amplify Authentication API を用いた Cognito の操作
 * ステートレスなバックエンドのための認証管理


Amazon Cognito を利用する上でこれらの開発の流れは必須になります。
このチュートリアルを通して Amazon Cognito の開発の流れのイメージを掴んでもらえれたら幸いです。
あとはプロダクションの環境に合わせて細かい設定を修正していただければセキュアな認証システムがサーバレスで導入できます。

著者もプロダクション環境で Amazon Cognito を利用したサービス開発を行っていますが、
簡単に認証機能が作成できて、助かっております。

ユーザの認証・管理方法の選択肢として firebase を利用する方法もあると思います。
firebase との明確な差は AWS サービスとの連携の容易さだと考えています。
認証済みユーザに IAM ポリシーをアタッチすることで簡単に別の AWS サービスの実行を許可したり
もしくは制限をかけたりすることができるのが強みだと思っています。
AWS メインのプロダクションの場合は検討してみるのもいいかと思います。

また、本書の別の章で Amplify と firebase との優位性の比較を行っている章がありますので是非そちらも参考にしてもらえればと思います。

== 付録
解説用に作成した Cognito サービスの認証チュートリアルのソースコードを GitHub に公開しています。
勉強などでお役に立ててもらえたら幸いです。

GitHub：@<href>{https://github.com/syoimin/my-new-project}


