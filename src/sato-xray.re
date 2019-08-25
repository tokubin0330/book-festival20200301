= AWS X-Rayで始めるパフォーマンス監視入門

== パフォーマンス監視について

みなさんはアプリケーションのパフォーマンス監視を行っていますか？

「ある特定の操作のときだけレスポンスが悪い」という状態は、
外形監視やメトリクスの監視だけでは気付くことが困難ですし、
監視ログからそれを探し出すにしても、しっかりとしたログ設計と分析体制を整えていなければ対応できません。
そして気付けないままある日、ユーザーからの問い合わせで発覚するという経験している方もいるのではないでしょうか。

そこで、転ばぬ先の杖ということでアプリケーション内部のパフォーマンス監視を行うためのマネージドサービスである AWS X-Ray をご紹介したいと思います。

== X-Rayとは

アプリケーションが処理するリクエストに関するデータを収集するサービスです。
分散トレーシングに対応しているため複雑化したマイクロサービスであってもリクエストを追跡が可能で、
SDKが対応している開発言語（環境）であれば、コードにはほぼ手を入れずにすぐに利用できます。

== X-Rayの導入

まずは、導入がかんたんな公式のX-Ray SDKを利用してみましょう。

今回はローカルにテスト用の実行環境を作るため、
@<ami>{AWS CLI}、@<ami>{Docker}、@<ami>{Docker Compose}が必要になります。
インストール方法は以下の各公式サイトを参考にしてください。

 * AWS CLIのインストール@<br>{}@<href>{https://docs.aws.amazon.com/ja_jp/cli/latest/userguide/cli-chap-install.html}
 * Dockerのインストール@<br>{}@<href>{https://docs.docker.com/install/}
 * Docker Composeのインストール@<br>{}@<href>{https://docs.docker.com/compose/install/}

インストールが完了したら各コマンドを叩いて、正常にインストールがされていことを確認しましょう。筆者の環境では下記のような表示になりました。

//cmd{
$ aws --version
aws-cli/1.16.166 Python/3.7.3 Darwin/18.7.0 botocore/1.12.156

$ docker --version
Docker version 19.03.1, build 74b1e89

$ docker-compose --version
docker-compose version 1.24.1, build 4667896b
//}

X-Rayへアプリケーション側からデータを送信するためにはX-Rayへの書き込み権限が必要になります。
ローカルで使用するユーザーに必要なIAMポリシーを設定します。

//cmd{
aws configure
//}



//list[iam][X-Rayの実行に必要なIAMポリシー]{
{
    "Version": "2012-10-17",
    "Statement": [
        {
            "Effect": "Allow",
            "Action": [
                "xray:*"
            ],
            "Resource": [
                "*"
            ]
        }
    ]
}
//}

//list[aa][ほげ]{
aaaa
//}

== 収集したデータの可視化と分析

== その他の使いかた

