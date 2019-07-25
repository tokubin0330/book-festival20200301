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

====[column]

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

====[/column]


