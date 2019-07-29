= AWSを使用して静的WordPressをデプロイする

== はじめに

私自身、WordPressでの開発・運用を10年近くに渡って携わって来ましたけど、ひたすら某G社のレンタルサーバーを愛用して来ました。
 
その理由はただ一つ！！
 
「安いから！！」「楽だから！！」
 
そもそもWordPressで運用しているサイトは、企業のコーポレートサイトなどが多いため耐久性や可用性に関する考慮は正直あまり必要ないという点はあります。
正直私自身もAWSでWordPressを運用するのは、余程のPVを集めるサイトではないとその必要がないと思ってきました。

ところがここ数年AWSを勉強していくにしたがって、AWSでも安くWordPressの運用ができるのではないかという可能性を感じるようになりました。
この章では、AWSを使用したWordPressの静的化と、そのデメリットとデメリットを実際に検証した結果を元に書いていきます。

== DockerでのWordPressの構築

基本的なWebサイトは、WordPressのようなフレームワークを通じて利用可能なプラグインや機能を使って、安全でない方法で作られることがよくあります。
ただし、多くの場合、これらのWebサイトは、静的サイトであるため、これらの機能が必要になるまでは必要ありません。
例えば、ポートフォリオや個人的なウェブサイトを持っているなら、それはおそらくHTMLとCSS（そして多分少しのJavaScript）だけで構成されていると思います。

=== DockerでWordPressを構築する

以下の手順でDocker環境を作っていきます。

 1. 空のプロジェクトディレクトリを作成します。
 2. そのディレクトリに移動します。
 3. 以下の内容でdocker-compose.ymlというファイルを作成します。
 4. プロジェクトディレクトリで、次のコマンドを実行します。
    docker-compose up -d
 * この時点でWordPressはlocalhostでアクセス可能になるでしょう。
 * localhost/wp-adminに移動してWordPressの設定を開始します。
 * 注：dockerコンテナーをシャットダウンするには
    docker-compose down --volumes 
    を実行してください。
 5. これで、Webサイトを変更する準備が整いました。

//list[viewer_docker-compose][docker-compose.yml]{
{
version: '3.3'
 
services:
   db:
     image: mysql:5.7
     volumes:
       - db_data:/var/lib/mysql
     restart: always
     environment:
       MYSQL_ROOT_PASSWORD: somewordpress
       MYSQL_DATABASE: wordpress
       MYSQL_USER: wordpress
       MYSQL_PASSWORD: wordpress
 
   cli:
     image: wordpress:cli
     volumes:
       - ./site:/var/www/html/
   
   wordpress:
     depends_on:
       - db
     image: wordpress:latest
     ports:
       - "80:80"
     restart: always
     environment:
       WORDPRESS_DB_HOST: db:3306
       WORDPRESS_DB_USER: wordpress
       WORDPRESS_DB_PASSWORD: wordpress
 
volumes:
   db_data:
}
//}

=== 静的WordPressをダウンロードしてAWS S3にデプロイする
WordPressサイトをホスティングすることは安全ではなく、費用もかかります。
静的にすることはこれらの欠点を最適化するための素晴らしい方法です、そしてそれをS3でホストすることはさらにコストを削減し、よりきめ細かいセキュリティ設定を可能にします。

以下の手順では、WordPressサイトから静的ファイルを生成し、それらをカスタムドメイン用に新しく構成されたAWS S3バケットでホストする方法について説明します。

 1. 「プラグイン」 > 「新規追加」 > wp2staticを検索 >「インストール」 >「有効化」の順にクリックします。プラグインが有効になったら、サイドパネルのwp2staticに移動してDeploy static websiteタブを選択します。
 2. タブの下にWhere will you host the optimized version of your site?のところにZIPアーカイブを選択します。次に保存をクリックします。
 3. Destination URLのところにS3に紐ついてるDomain名を入れます。
 4. Start static site exportを押すとzipで静的ファイルのダウンロードできます。

=== S3バケットの設定

 1. AWSにサインインします。S3に移動して新しいバケットを作成します。ドメインの名前を付けます。例えばshowcase-tv.comです。
 2. 次に、バケットポリシーを作成する必要があります。AWSにはこの便利なポリシージェネレータがあります。
 ジェネレータを使用したくない場合は、AWSのドキュメントにもかなり良い例があります。

//list[viewer_generator][generator_example]{

 Type of policy:：S3 Bucket Policy
 Effect: Allow
 Principal: *

 AWSサービス：Amazon S3（これはポリシーの種類に応じて自動的に設定されます）
 Actions：GetObjectのみ

 AmazonResourceName（ARN）：これはドメイン名に依存しますが、同じフォーマットになります。例えば：
 arn：aws：s3 :::showcase-tv.com/*

//}

 3. パケットポリシー

//list[viewer_packetpolicy][packetpolicy]{

{
    "Version": "2012-10-17",
    "Statement": [
        {
            "Sid": "AllowPublicReadAccess",
            "Effect": "Allow",
            "Principal": "*",
            "Action": "s3:GetObject",
            "Resource": "arn:aws:s3:::showcase-tv.com/*"
        }
    ]
}

//}

