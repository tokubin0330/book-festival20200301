= Amplifyでつくるプランニングポーカー

== はじめに
今回Amplifyをテーマに記事を書こうと思ったきっかけは、AWSが開催しているDev Day Challengeに出場した背景があります。
Hackathonでは16チームが発表を行ったのですが、そのうちの数チームがAmplifyを導入したプロジェクトの作成を試みておりました。
他のチームの導入している技術の目新しさに若干の危機感を覚えました。
そこから半年近くたった現在、本番環境にAmplifyを使ってサービス開発をするまでに至りましたがその過程は困難を極めます。

 * Amplify関連の日本語説明/ドキュメントが少ない
 * そのためAmplifyを紹介している日本語のブログも入門程度にしか触れられていない
 * AppSync/GraphQLという新しい概念の習得や各種サービス仕様の調査が難しい
 * Apollo ClientというGraphQL向けフレームワークの把握
 * 結局Amplifyだけで完結することが難しい

後述するFirebaseと比較しても少し出遅れている感が否めませんが、
だからこそ記事にすることによって少しでも貢献できればと考えた次第です。
個人的な見解ですが、すでにAWSを導入している企業にとってはAmplifyを使うメリットはあると思います。
フロントエンドだけでは完結しない処理を複数のAWSサービスと連携をするときなどにおすすめです。
今回は1つのWebサービス開発を通じてAmplifyの説明をおこなっていきたいと思います。
特に@<strong>{API}という機能で使用するAppSync/GraphQLについて大半のページを割いておりますので、少しでもお役に立てれば幸いです。

== Amplifyの概要
AWS Amplifyをご存知でしょうか。簡単におさらいしたいと思います。

=== Amplifyとは
Amplifyとは何かについて公式ページより引用をしたいと思います。
@<br>{}
@<href>{https://aws.amazon.com/jp/amplify/faqs/}
//quote{
AWS Amplify は開発フレームワークおよび開発者用サービスで構成されており、モバイルアプリケーションやウェブアプリケーションを AWS で構築するための最も速くて簡単な方法を提供します。オープンソースの Amplify フレームワークでは、主観的な一連のライブラリ、UI コンポーネント、コマンドラインインターフェイスを利用できるため、アプリケーションバックエンドを構築して、iOS、Android、ウェブ、React Native の各アプリケーションと統合できます。Amplify フレームワークは、主要な AWS クラウドサービスを活用して、オフラインデータ、認証、分析、プッシュ通知、ボット、AR およびバーチャルリアリティなどの機能を大規模に提供しています。AWS Amplify 開発者用ツールサービスには、ウェブアプリケーションを構築、デプロイ、ホストする AWS Amplify コンソールと、モバイルアプリケーションを iOS デバイスおよび Android デバイスの実機でテストする AWS Device Farm が含まれています。
//}
前の章でAmplifyの説明をしているページがありますので(@<hd>{shiomi-cognito|Amplify フレームワーク を利用した Cognito 認証アプリ|Amplify の概要})ご参照ください。
BaaS+関連するUIコンポーネント付きという捉え方もできますし、「今まで使っていたAWSの各種サービスを使いやすくセットアップしてくれるサービス」という考え方もできます。
つまりAmplifyを使用するとしても裏側ではAWSの各種サービスを利用しています。
//quote{
AWS AppSync、Amazon Cognito、Amazon Pinpoint、AWS Lambda、Amazon S3、Amazon Lex
//}
公式ページに記載されているサービスは上記の通りですが、
他にも以下のサービスなどが使用されています。

 * Amazon DynamoDB(AppSyncのバックエンド)
 * Amazon Elasticsearch Service(AppSyncのバックエンド)
 * Amazon CloudFront(Hosting)
 * AWS CloudFormation(Amplifyのセットアップ)

上記のサービスの組み合わせを提供し、開発者はそれを利用することで容易かつ安全にアプリケーションの開発を行うことができます。

=== Amplifyを開発するにあたって苦労した点
さて一見便利そうなAmplifyではありますが、導入にあたって苦労をした点があります。

 1. SPA(SinglePageApplication)による開発が主になるのでOGPなどの対応が難しい
 2. 複雑なアプリケーション開発をする場合に、Amplifyだけでは解決できない

Amplifyで開発をおこなうと、React.jsやVue.jsなどを用いたサービス開発になりますので、
SPAの環境になります。
OGPに関しては現状各種SNSサービスがjsを解釈してくれないため、
固定値のheadタグを埋め込まなければいけません。
そうすると、ページごとのURLを各種SNSに貼り付けた際に、
個別のtitleを表示できず全ページ共通のタイトルになってしまいます。
これを解決する方法としてLambda@Edgeという機能を使って解消ができますが、
後者の問題にあたります。結局、少しでも複雑なアプリケーションを開発する場合にはAmplifyだけでは足りない現状です。

#@#  * 定期的にバッチを動かすような機能
#@#  * いいね数や閲覧数を集計してランキング表示するような機能
#@#  * S3に画像や動画がアップロードされたことをトリガーに加工を行う機能

#@# こういう機能を実装することになるとAmplifyだけでは足りなくなります。
#@# ではどうするかというと、現状はAmplifyで作ったサービスとは別にプロジェクトを作るわけです。
#@# そうなるとAmplifyで全部管理をしていた状態から外れるわけですので、
#@# 煩雑な管理体制となり、「あれ？では最初からAmplifyを使わなくてもいいのではないか？」
#@# というモヤモヤした状態になるかと思われます。

=== AmplifyとFirebaseの比較
BaaS界隈の有名サービス@<strong>{Firebase}と比較してAmplifyはどうでしょうか。
私なりにいくつか見解を述べさせていただきます。

==== できるだけ初期はコストを抑えたい
この場合Firebaseをおすすめします。Firebaseには無料で利用できる範囲が定められており、
クレジットカードの登録すら必要なくプロジェクトを開始することができます。
@<href>{https://firebase.google.com/pricing/?hl=ja}
@<br>{}
Firebaseもいくつかのプロジェクトで利用したことがありますが、
スケールする前までは無料の範囲内で賄うことができてしまいます。
機能もAmplifyと遜色がなく、

 * 認証
 * ストレージ
 * データベース(Realtime Database/Cloud Firestore)
 * Hosting

などの主要なサービスは全て揃っています。

==== 日本語のドキュメント/サンプルが多い方がいい
この場合も採用するべきはFirebaseです。日本語に限らずですが、世界的にFirebaseの方が利用されているためサンプルも解説もとても多いです。
現状Amplifyで何かトラブルが発生した場合は、英語のドキュメントやStackOverflowを眺めながら
試行錯誤を繰り返して解決しなければなりません。サーバーレスにより楽をしたい反面、結果的にわからない範囲が多く調査に時間を取られてしまいます。

==== プッシュ通知などのアプリケーション開発を行いたい
この場合もまだFirebaseをおすすめします。Amplifyから使用できるプッシュ通知サービスはAWS SNSではなくPinPointになります。
2019年3月現在東京リージョンがまだなく、管理画面も日本語対応されていない状況のため、操作はFirebaseの方が簡単です。

==== React.jsによる開発をおこないたい。
個人的にはややAmplifyを導入することをおすすめいたします。
FirebaseがVue.jsのサンプルが多いのに対し、AmplifyはReact.jsのサンプルの方が多く記載されています。

==== GraphQLを導入したい
AWS AppSyncがありますのでAmplifyを導入するのがよいでしょう。

==== AWSの知見や資産を活用したい。
Amplifyを選択する最大のメリットです。
先述した通りですが、Amplifyで動いている各種機能のバックグラウンドにはAWSのサービスが使われているので、サービスの連携がとても容易に行えるかと思います。
また個人的にはサービスを分割することでのチーム開発もしやすくなるかと考えています。

 * AmplifyのStorageモジュールでS3に画像をアップロード(Aさん)
 * 任意のStorageに画像がアップロードされたら、縮小して別のS3バケットにアップロードする(Bさん)
 * 縮小したサイズの画像がアップロードされたらフロントに対してPubSubやAPIを経由して通知を行う(Cさん)

というようなサービスの分割による開発もしやすいかと思います。

#@# //embed[latex]{
#@# \clearpage
#@# //}

#@# == プランニングポーカーについて

#@# さて今回はAmplifyの機能を最大限活用しながら、デメリットの少ないサービスとしてプランニングポーカーを考えました。
#@# この開発を通じてAmplify(特に一番重要なAPIの部分)を解説していきたいと思います。
#@# また今回のプロジェクトのサンプルは最後にご紹介します。

#@# === プランニングポーカーとは

#@# プランニングポーカーをご存知の方は多いかと思いますが、改めてご説明をさせてください。

#@# @<href>{https://japan.zdnet.com/keyword/%E3%83%97%E3%83%A9%E3%83%B3%E3%83%8B%E3%83%B3%E3%82%B0%E3%83%9D%E3%83%BC%E3%82%AB%E3%83%BC/}

#@# //quote{
#@# アジャイル開発プロジェクト管理用語。Mountain Goat SoftwareのMike Cohn氏が考案した見積もりゲーム。プランニングポーカーは、各ユーザーストーリーの見積もりをチームアクティビティとして行うために用いられる。プランニングポーカーでは、チームが集まって一度に1つのユーザーストーリーをレビューする。ストーリーが示されると、チームはそのユーザーストーリーについて話し合い、自分のデッキから、作業見積を示すカードを出す。チームが合意に至るまで、全員が見積もりを示し、議論することを繰り返す。
#@# //}

#@# 例えば「ログイン」という機能があったとしてみなさんはどのような作業見積もりをするでしょうか。
#@# 私は業務上よく見積もりをするのですが、曖昧なスケジュールや仕様を想定したまま見積もりをすることがあるため、
#@# できるだけ正確にプロジェクト参加者全員の共通理解のもと見積もりを行いたいと考えております。
#@# このカードゲームを通じて全員の見積もりの見解をすり合わせ、あるいはお題が曖昧な部分に関しては深掘りすることによって
#@# より正確な見積もりを行うことが可能になります。

#@# === 作ろうと思った経緯

#@#  * 手元にカードがなくてももっと手軽にプランニングポーカーをしたいよね。
#@#  * そもそもみんなどういう尺度のポーカーをしているか気になる。
#@#  * フリーのサービスにして色んなエンジニアの考えを集められたら
#@#  * Amplifyをフル活用できるようなサービスがないかな〜

#@# プランニングポーカーはトランプのようなカードを利用し、お互いに手札を隠したまま場に出しあうというものなので、
#@# 親と子の関係の画面がありそれらがリアルタイムに通信をする必要があるため、
#@# AmplifyのAppSyncの機能を最大限活用してプランニングポーカーを実装ができそう！
#@# そしてそれを網羅的に解説できそう！と思ったことが一番大きい動機です。

#@# //embed[latex]{
#@# \clearpage
#@# //}

#@# == 要件を定義する

#@# === プランニングポーカーに必要な機能とは
#@# いくつか考えた要件を記載したいと思います。

#@#  * 親と子画面がある
#@#  * 親がルームを作成してURLを共有。子はそのURLからルームに入れる
#@#  * 親がお題を決めたら、子の画面の方にリアルタイムにお題が共有される
#@#  * この画面で共有されたお題に対して答えを送信すると親の画面にカードが飛んでいく
#@#  * ルームにはパスを設定して鍵をかけることもできたらいいよね
#@#  * カードは基本的なプランニングポーカーの数字もありながら他の用途（満足度評価やクイズ）にも使えそう。
#@#  * テンプレートを選べたりフリーテキスト入力があってもいいよね
#@#  * ２段階見積もり(ミニマム/マックス)をやるケースもあるから出せるカードの枚数は数枚出せるパターンも用意（n枚縛り）
#@#  * クイズにしたら事前に回答者の画面みれるようにしたいよね。（平成教育委員会のような）
#@#  * 親画面に近い画面をもう１つ用意、そちらはめくられた状態。事前に正解がどうか決められる

== 画面を作ってみよう
さて、ここからは考えた要件をもとにアプリケーションを開発してみましょう。

=== Reactのプロジェクトを作成
Amplifyの初期ページにも記載があるので確認していきましょう。

@<href>{https://aws-amplify.github.io/docs/js/start?platform=react}

//cmd{
$ npm install -g create-react-app
$ create-react-app myapp && cd myapp
$ npm start
//}

ここでアプリケーションを実行すると、
ブラウザが起動しReact.jsのロゴが回転しているようなページが表示されていれば成功です。
ここから徐々にカスタマイズしていきましょう。

=== URLに応じて表示するページを切り替える
まずは、URLごとに表示するページを変更するために、
react-routerというライブラリーをインストールします。

//cmd{
$ npm install --save react-router
//}

その後プロジェクトファイル内に用意されている、App.jsに対して下記のようにルーティング情報を設定します。
※これからソースコードをいくつか記載しますが、ファイルの一部を抜粋しております。

//listnum[router][App.js][js]{
import { BrowserRouter as Router, Route } from 'react-router-dom';

const App = () => (
  <Router>
    <div>
      <Route exact={true} path="/" component={NewProject} />
      <Route exact={true} path="/project/:id" component={PockerField} />
      <Route exact={true} path="/project/:id/player" component={PlayerField} />
      <Route path="/newProject" component={NewProject} />
    </div>
  </Router>
);
//}
この場合、例えばhttp://aaa.com/というURLの場合
//table[routing][ルーティング例]{
パス	表示コンポーネント	ページ説明
---------------------------------
aaa.com/	NewProject	新規プロジェクト作成ページ
aaa.com/project/123	PockerField	カードが並ぶ親の画面
aaa.com/project/123/player	PlayerField	お題に対してカードを出す子の画面
aaa.com/newProject	NewProject	新規プロジェクト作成ページ
//}
という仕組みになっています。

また「:id」のところを例として表には「123」と記載しておりますがどんな文字列でも構いません。
上記の場合コンポーネント側ではidというkeyで123という数値が取得できるようになっています。
//listnum[params][ReactRouterでパラメーターを取得する例]{
componentDidMount() {
  const { id } = this.props.match.params;
  ----- 以下取得したidを元に色んな処理を行う -----
}
//}

=== ページごとのコンポーネントの作成
次にreact-routerで作成したコンポーネントごとにページを作成します。
全部を表示するにはページ数がたりませんので、NewProjectコンポーネントのみ
ご紹介させていただきます。
@<br>{}
※これからいくつかのソースコードを記載いたしますが、抜粋しております。
//listnum[newproject][NewProject.jsx][js]{
----- 省略 -----
render() {
  return (
    <div className="ui container">
      <div className="ui form">
        <div className="field">
          <label>プロジェクト名</label>
          <input type="text" placeholder='Project name' />
        </div>
        <div className="field">
          <label>プロジェクト詳細</label>
          <input type="text" placeholder="Project description" />
        </div>
        <button>Add Project</button>
      </div>
    </div>
  )
}
----- 省略 -----
//}

この状態でアクセスして確認してみましょう。
npm startしている状態の場合は、ファイルを保存するだけで更新されます。
表示はこのような状態になります。
@<br>{}
http://localhost:3000/
//image[newproject][NewProject.jsx][scale=0.8]

=== トランプのコンポーネントとそれをめくるギミックの作成
トランプをめくるアニメーションについてはDOMでやるかCanvasなどを活用するかを
検討した結果div+CSSでもイメージに近いめくるアニメーションのサンプルが見つかりましたので、
そちらを参考にCSSを当てて行きたいと思います。
@<br>{}
@<href>{https://3dtransforms.desandro.com/card-flip}
@<br>{}
こちらのページを参考にカードのコンポーネントを作成します。

//listnum[card][カード][js]{
import React, { Component } from 'react';

export default class Card extends Component{
----- 省略 -----
render(){
  return(
    <div className="card">
      <div className="card__face card__face--front">
        <p>
          {this.props.frontText}
        </p>      
      </div>
      <div className="card__face card__face--back">
        <p>
          {this.props.backText}
        </p>
      </div>
    </div>
  )
}
----- 省略 -----
//}

カードをリスト上に並べて表示してみます。
//image[cards][PockerField.jsx][scale=0.8]
他のコンポーネントも作成したら次はcssをあててレイアウトを少しリッチにして行きたいと思います。

#@# //embed[latex]{
#@# \clearpage
#@# //}

=== SemanticUIの導入
大枠の画面ができあがったら次は画面のUIをリッチにするためにCSSを記載していきます。
しかし、自分でCSSを書くのが少し面倒！ということでSemanticUI@<fn>{semantic}を導入しました。
npmでインストールする方法とCDNを使って読み込む方法があります。
個人的にはCDNが好きで手っ取り早いのでindex.htmlにSemanticUIの各種モジュールを読み込みます。

//footnote[semantic][CSSフレームワークの１つ。他にもBootStrapなどが有名です。https://semantic-ui.com/]

//listnum[semanticui][SemanticUIの読み込み][html]{
<link rel="stylesheet" href="https://cdn.jsdelivr.net/.../semantic.min.css">
<script src="https://cdn.jsdelivr.net/.../semantic.min.js"></script>
//}

semantic-uiを読み込んだ後に各種ElementをSemanticUIにそうようなクラス名@<fn>{className}をつけて行きます。
//footnote[className][React.jsではクラス名を<div class="">ではなく<div className="">と記載します。]
事例としてボタンのUIの紹介をいたします。先ほどのNewProject.jsxの送信ボタンを
//listnum[newbutton][クラス名をつけたボタン][js]{
<button className="ui teal button">Add Project</button>
//}
として表示してみると、
//image[semanticbutton][SemanticUIのButton][scale=1]
少しリッチなUIになりました。
全部のページにSemanticUIを反映して行きます。

== APIの導入
さあ、ここまできたのでようやくAmplifyを導入していくことにしましょう
//cmd{
$ amplify init
//}
ここで対話形式に質問をされます。

 * 使用しているエディター
 * アプリのタイプ(iOS/Android/Web)
 * 使用するフレームワーク
 * ディレクトリーパス関連
 * コマンド実行の書き方
 * どのAWSアカウントを利用するか

その後CloudFormationが実行され認証(AuthRole)/未認証(UnauthRole)ユーザー用のIAMロールが作られます。
次にAPIをプロジェクトに追加するためのAmplifyコマンドを実行します。
//cmd{
$ amplify add api
//}
ふたたび対話形式にいくつかの質問を受けます。

//cmd{
? Please select from one of the below mentioned services (Use arrow keys)
> GraphQL
  REST
//}

今回はGraphQLの紹介をしますので、そのまま進めます。
//cmd{
? Please select from one of the below mentioned services GraphQL
? Provide API name: myNotesApi
? Choose an authorization type for the API (Use arrow keys)
> API key
  Amazon Cognito User Pool
//}
これはAPI KeyによってAPIに接続するかAuthで作られるUserPoolの情報によって接続するかが聞かれます。
API Keyはあくまでテスト的に発行される情報なので７日間で失効します。
しかし導入は簡単なのでAPI Keyを選択しましょう。
@<br>{}
質問を続けていくとサンプルのschemaを作るか聞かれます。
//cmd{
? Do you want a guided schema creation?
//}
trueにすると、
//cmd{
> Single object with fields (e.g., “Todo” with ID, name, description)
  One-to-many relationship (e.g., “Blogs” with “Posts” and “Comments”)
//}
と２つのサンプルから選択できますが、あとから編集をかけるのでどちらでもいいでしょう。
複雑なリレーションシップになっているのは後者ですので、みてみたい方は選択してください。

最後に、
//cmd{
? Do you want to edit the schema now? (Y/n)
//}
と言う感じで今すぐにschemaを編集するかするかを聞かれます。
@<br>{}
次の章で今回使用するプロジェクトのSchemaを定義して行きたいと思います。

=== Schemaの設計
AppSyncで使うためのSchemaを定義します。
AppSyncの基盤はGraphQLとなっておりますので基本的にはGraphQLと同等の書き方ができます。
モデルを作成する前に、それぞれにどのような型があるか簡単におさらいしてみましょう。

==== GraphQLスカラー型

 * ID
 * String
 * Int
 * Float
 * Boolean

==== AppSyncスカラー型
GraphQLの型以外にもAppSyncで使用できる型があります。詳しくはこちらを参照してください。
@<br>{}
@<href>{https://docs.aws.amazon.com/ja_jp/appsync/latest/devguide/scalars.html#aws-appsync-scalars}

 * AWSDate YYYY-MM-DD の形式の日付文字列を受け入れます。
 * AWSTime hh:mm:ss.sss の形式の時刻文字列を受け入れます。
 * AWSDateTime YYYY-MM-DDThh:mm:ss.sssZ の形式の日時文字列を受け入れます。
 * AWSTimestamp 1970-01-01T00:00Z から経過した秒数を表します。
 * AWSEmail RFC 822 に準拠する E メールアドレス文字列を表します。
 * AWSJSON RFC 8259 に準拠する JSON 文字列を表します。
 * AWSURL URL にはあらゆるスキームを使用でき、ローカル URL (例: <http://localhost/>) であっても構いません。
 * AWSPhone 有効な電話番号を表現します。電話番号は文字列としてシリアル化および逆シリアル化されます。
 * AWSIPAddress 有効な IPv4 または IPv6 アドレス文字列を表現します。

==== オブジェクト型の定義
上記のスカラー型を参考に今回のプロジェクトで使用するオブジェクト型を定義しました。
こちらも長くなるのでポイントのみ絞ってご紹介いたします。
//listnum[schema][schema.graphql]{
type Project @model {
  id: ID!@<fn>{ID!}
  title: String!
  password: String
  description: String
  limitCard: Int
  topics: [Topic] @connection(name: "ProjectTopics", sortField: "createdAt")
  players: [Player] @connection(name: "ProjectPlayers")
  template: Template @connection(name: "TemplateProjects")
}

type Topic @model{
  id: ID!
  title: String!
  description: String
  createdAt: String
  point: Int
  projectId: ID!
  project: Project @connection(name: "ProjectTopics", sortField: "createdAt")
  answers: [Answer] @connection(name: "TopicAnswers", sortField: "createdAt")
}

type Player @model {
  id: ID!
  projectId: ID!
  answers: [Answer] @connection(name: "PlayerAnswers")
  project: Project! @connection(name: "ProjectPlayers")
  user: User! @connection(name: "UserPlayers")
}

type User @model {
  id: ID!
  name: String
  image: String
  players: [Player] @connection(name: "UserPlayers")
}
//}


//footnote[ID!][!はnon-nullをさします。nullを許可しません。]

===== ポイント① GraphQLトランスフォーマー
上記スキーマに@model @connectionといったアノテーションがついた表記があります。
それぞれを定義することで以下のような設定が可能になります。
//table[routing][ルーティング例]{
Directive	説明
---------------------------------
@model	DynamoDBテーブルの作成とCRUDリゾルバーの設定@<br>{}例えばtype Project @modelの場合@<br>{}DynamoDB上にProjectテーブルが作成され、@<br>{}生成/読み取り/更新/削除が可能になります。
@connection	@modelオブジェクト間のリレーションシップを指定します。@<br>{}上記schemaの場合は、ProjectとTopicは1対多の関係になります。
//}
今回のサンプルでは使用しておりませんが、認証と連動する@authディレクティブや検索のための@searchableディレクティブなどがあります。

===== ポイント② 配列のソート(sortField)
上記スキーマで@connectionディレクティブでsortFieldという記載しています。
ProjectとTopicが１対多の関係になっており、Projectに紐づいているTopicの一覧を取得する場合
明示的に指示を出さないとID順でリストが取得されます。
いや、そうではなく新着順で並べたいんだという場合以下のような方法があります。
@<br>{}
一旦データをAPIで取得してからjs側で並び替えを行うコードとしてはこのような形になります。
//listnum[sort][jsのソートサンプル]{
topics.items.sort(function(a,b){
    return (a.createdAt > b.createdAt) ? -1 : 1;
});
//}
一見簡単そうに見えますが、問題が１つあります。
APIでリストのデータを取得する場合、@<strong>{引数に件数を明示しないと10件までのデータしか取得できません。}
例えば一度に100件データを取得したい場合はlimitに100という数値を渡す必要があります。
//listnum[list][queryのサンプル]{
listProjects(filter: ModelProjectFilterInput, limit: Int, nextToken: String)
//}
しかし、@<strong>{全体で何件のデータ登録があるかはわからない}のでこちらのlimitの数値が適切ではない可能性があります。
その課題をクリアするために、
schemaの設計時にmodelの何を軸としてソートをするかを指示することができます。
createdAtはDynamoDBのテーブルが作成される際に標準で生成されるカラムになり、
作成された時間が登録されているので並び替えのFieldをcreatedAtにすることで、
新着順の並び替えが可能になります。createdAtもSchemaに記載しておかないと、並び替えできませんのでご注意ください。
また、指定した件数以上のデータを読み込む場合には取得したnextTokenを渡す必要があります。
上記の場合projectに紐づくtopicsの追加件数分のリストを取得することになりますので、下記のようなコードになります。
//listnum[nextToken][子要素の追加○件を取得する場合の例]{
const getProject = `query GetProject($id: ID!,$nextToken: String) {
  getProject(id: $id) {
  ---- 省略 ----
    topics(nextToken:$nextToken) {
      items{
        id
        title
      }
    }
  ---- 省略 ----
  }
}
//}

===== ポイント③ 多対多のリレーションシップ
基本的にRDBなどと変わりませんが1toMto1のスキーマを定義すれば対応が可能です。
schemaを例に言うと、
Projectに紐づく(参加する)多のPlayerが存在し、
Userに紐づく多のPlayerが存在します。
Playerモデルを通じて、Userは複数のProjectに参加でき
Projectに複数のUserが参加できることになります。
またAppSyncではSchema設計を複雑にすることがバッドプラクティスとされていますのでご注意ください。

=== Query/Mutation/Subscriptionについて
上記はモデルだけ定義してあるので、読み取りや書き込みなどの指示がまだ存在しておりませんので、作成して行きます。
まずGraphQLには３つのトップレベルオペーレーションがあります。

 * Query:データの読み取り(get/list)
 * Mutation:データの書き込み(create/update/delete)
 * Subscription:データの受け取り

SubscriptionはMutationに対する応答として呼び出されるものです。
MQTT over Websocketにとって実装されており、
例えばSubscriptionでProjectモデルがcreateされることをsubscribeしている場合、
任意の誰かがProjectを作成した瞬間に、subscribeしている他の端末にリアルタイムにデータが送られます。
これをプランニングポーカーに応用すると、

 * お題を出す(createTopic)
 * お題を出すをsubscribeしている端末にお題が届く
 * お題に対して答えを選択するして送信する(createAnswer)
 * 親の端末では答えを出すをsubscribeし、子の端末が答えを出すごとにリアルタイムにカードが飛んでくる

というような流れができます。
@<br>{}
そこに先述してあるカードをひっくり返すギミックを組み合わせれば、
お題の答えを一斉にオープンなどといったことができるようになるわけです。
さて話が長くなりましたがそれぞれのオペーレーションを作成してみましょう。

==== AmplifyでQuery/Mutation/Subscriptionを作成する
実はAmplifyでQuery/Mutation/Subscriptionを生成するのは非常に簡単です。
上記のschemaのように適切なmodelやconnectionが記載されていれば、
あとは自動で作成してくれます。

//cmd{
$ amplify push
//}

push時に以下の項目の質問を受けます。全部Yで問題ありません。
//cmd{
? Are you sure you want to continue? (Y/n)
? Do you want to generate code for your newly created GraphQL API (Y/n)
? Enter the file name pattern of graphql queries, mutations and subscriptions (src/graphq
? Do you want to generate/update all possible GraphQL operations - queries, mutations and
 subscriptions
//}

一番最後が質問が重要です。
選択すると全てのモデルに対してqueries,mutations,subscriptionsなどを生成してくれます。
逆に言うと、このモデルはsubscriptionsはいらないなど個別に対応はできませんので、
その場合には自力で必要なオペーレーションを記載しましょう。
//listnum[manualoperation][手動作成コード例(backend/api/schema/PATH/schema.graphql)]{
type Subscription {
 subscribeToProjectPlayers(projectId: String!): Player 
  @aws_subscribe(mutations : ["createPlayer"])
 subscribeToProjectTopics(projectId: String!): Topic 
  @aws_subscribe(mutations : ["createTopic"])
 subscribeToTopicAnswers(topicId: String!): Answer 
  @aws_subscribe(mutations : ["createAnswer"])
}
//}

自動生成した場合の出来上がりコードはこちらです。
AppSyncの管理画面にアクセスして確認しましょう。
//listnum[operations][自動生成コード例(#current-cloud-backend/api/PATH/build/schema.graphql)]{
type Subscription {
	onCreateProject: Project
		@aws_subscribe(mutations: ["createProject"])
	onUpdateProject: Project
		@aws_subscribe(mutations: ["updateProject"])
	onDeleteProject: Project
		@aws_subscribe(mutations: ["deleteProject"])
  ---- 省略 ----
}

type Query {
	getProject(id: ID!): Project
	listProjects(filter: ModelProjectFilterInput,limit: Int,nextToken: String)
  ---- 省略 ----
}

type Mutation {
	createProject(input: CreateProjectInput!): Project
	updateProject(input: UpdateProjectInput!): Project
	deleteProject(input: DeleteProjectInput!): Project
  ---- 省略 ----
}
//}
====[column]@aws_subscribeについて
@aws_subscribeというアノテーションについての補足説明になりますが、
()内に記載があるイベントが発動した時に関数が発動するという指示になります。
例えば、onCreateProject: Project @aws_subscribe(mutations: ["createProject"])という記載がある場合は、
MutationのcreateProjectというイベントが実行された時にonCreateProjectが呼び出されることになります。

====[/column]

上記で作成されたSchemaが反映されたコードをローカルにjavascriptファイルとして生成ができます。
//cmd{
$ amplify codegen
//}

 * src/graphql/mutations.js
 * src/graphql/queries.js
 * src/graphql/schema.json
 * src/graphql/subscriptions.js

これらのjsをコンポーネント側に読み込み、
APIのgraphql関数を実行することで全てのCRUD操作とsubscriptionが可能になります。
出力されたコードについて気をつけていただきたいのはschemaにアップデートがあるたびにcodegenを実行すると、
ファイルが全て上書きされてしまいます。後述するデータの拡張を手動で行う場合には全て元に戻ってしまうので、
ファイルの修正などが入る場合には、自分でファイルを実装してそこから呼び出すようにしましょう。

=== GraphQLサーバーとデータのやりとりをする
前節まででschemaの作成とjsファイルの生成ができましたので、いよいよWebアプリに組み込んで行きたいと思います。
@<href>{https://aws-amplify.github.io/docs/js/api,公式ページ}では大きく３つの方法を紹介しています。

 1. AmplifyGraphQLClient
 2. AmplifyGraphQLClient用ReactComponentのConnectを使用する
 3. AppSyncSDK

最初にGraphQLやAppSyncの理解を深めるためには最初に紹介したシンプルなGraphQLClientを試してみるのをお薦めいたします。
今回のWebアプリについてはAppSyncSDKを使用しております。興味のある方はそちらを参照してください。
１番と２番に使われている技術はAmplifyを使用しているためほぼ同じです。
//listnum[import][import graphql]{
import Amplify, { graphqlOperation }  from "aws-amplify";
import { Connect } from "aws-amplify-react";
import * as queries from './graphql/queries';
import * as mutations from './graphql/mutations';
import * as subscriptions from './graphql/subscriptions';
//}

３番に関しては割愛いたしますが、興味がある方はこちらよりみてみてください。
@<href>{https://aws-amplify.github.io/docs/js/api#aws-appsync-sdk}

== デプロイ
最後にデプロイを行います。
Amplifyでは２種類のデプロイがあります。

 * DEV: only S3 static web hosting
 * PROD: S3 and CloudFront

本番デプロイをするまではDEVのS3のみで問題ないでしょう。
ローカル環境でもnpm startで確認はできますが後述している(@<hd>{余談|Apollo Client使用時にAppsyncの取得がブラウザによって挙動が違う場合})ブラウザ環境の問題もありますので、
早めにデプロイしておくことをお薦めいたします。

//cmd{
$ amplify publish
//}

特に取り上げる内容もありませんが、
ドメインについてはAmplify上では取得できませんので、別途Route53@<fn>{route53}などのサービスを利用するようにしてください。
SSL証明書(AWS Certificate Manager)なども同様です。
//footnote[route53][AmplifyでRoute53を導入するためのセットアップ方法。@<href>{https://docs.aws.amazon.com/ja_jp/amplify/latest/userguide/custom-domains.html}]


== 出来上がりはこちら

//image[kansei][完成イメージ][scale=0.8]

== 余談
Webサービスを開発中に気づいた細かいTIPSを共有いたします。

=== Prodデプロイしたホスティングのキャッシュをクリアしたい場合
作成したWebアプリをデプロイする際に一度CloudFront上に公開された静的ファイルはキャッシュが残っておりますので、
クリアする必要があります。その場合は、
//cmd{
$ amplify publish -c
//}
-cオプションを利用することでCloudFrontのキャッシュをクリアすることができます。

=== appsyncのarnを取得するには
//cmd{
$ aws appsync list-graphql-apis --profile [aws_profile]
//}
取得できたarnをIAMに使用してアクセスのコントロールを行ってください。

=== amplify apiで生成されたjsonよりネストが深いデータにアクセスしたい場合
amplifyでapiのschemaを作成後、codegenでschemaにアクセスするための各種jsonデータが生成されます。しかし、ここで生成されるデータは１階層までとなります。
Project=>Topics=>Answersという関係性の場合、生成されたデータではProjectからAnswerのデータにアクセスすることができません。
その場合の解決方法はjsonのデータを自分で追記することで解決できます。
//listnum[json1][旧queries.json]{
getProject(id: $id) {
  topics {
    items{
      id
    }
  }
}
//}
から下記に変更をします。
//listnum[json2][新queries.json]{
getProject(id: $id) {
  topics {
    items{
      id
      answers{
        items{
          id
          text
        }
      }
    }
  }
}
//}

=== Apollo Client使用時にAppsyncの取得がブラウザによって挙動が違う場合
mobile safariのプライベートモードなどだと、graphqlのデータが取得できないなど挙動に不安定な場合があります。
その場合にはAppSyncClientを呼び出す際に一行追加をしてください。
//listnum[appsyncclient][AppSyncClient]{
disableOffline:true
//}

#@# === QRコードが読み取り難しいケース
#@# QRコードは上下左右に余白(QRコードの文字色と違う背景色)が無いと読み取りができないです。
#@# //image[qr][QRコード表示例][scale=0.8]
#@# 上下余白をQRコードの周りにつけましょう。みなさんご存知でしたか？

== まとめ
さてページ数とスケジュールの都合上全部の内容を紹介するわけには行きませんでしたが、
ポイントは以下の通りです。

 * Amplifyはまだまだ日本には浸透されていない
 * 利用すると色々と気づける部分が多い
 * amplify add apiでGraphQLのschemaを作成
 * @model @connectionといったディレクティブを有効に使う
 * codegenでプログラムに組み込んで使用する。上書きされてしまうので、データを拡張する場合は独自実装する。
 * 読み込む場合はAmplify ClientもあればApollo Clientなどもある。最初はAmplify Clientが始めやすい。

また、細かいコードなどは書籍のページの都合上割愛させていただきました。
興味のある方はこちらのリポジトリよりダウンロードしてください。
@<br>{}
@<href>{https://github.com/wataruiijima/planning-poker}
@<br>{}
このプランニングポーカーアプリは機能を追加して皆さんにお使いいただけるように、準備をしております。
技術書典までに間に合え！！