::LANG
::yarn run write-translations -- --locale LANG
::mkdir i18n\LANG\docusaurus-plugin-content-docs\current
::copy docs\** i18n\LANG\docusaurus-plugin-content-docs\current
::mkdir i18n\LANG\docusaurus-plugin-content-blog
::copy blog\** i18n\LANG\docusaurus-plugin-content-blog
::mkdir i18n\LANG\docusaurus-plugin-content-pages
::copy src\pages\**.md i18n\LANG\docusaurus-plugin-content-pages
::copy src\pages\**.mdx i18n\LANG\docusaurus-plugin-content-pages

::English (GB)
yarn run write-translations -- --locale en-GB
mkdir i18n\en-GB\docusaurus-plugin-content-docs\current\
copy docs\** i18n\en-GB\docusaurus-plugin-content-docs\current\
mkdir i18n\en-GB\docusaurus-plugin-content-blog\
copy blog\** i18n\en-US\docusaurus-plugin-content-blog\
mkdir i18n\en-GB\docusaurus-plugin-content-pages\
copy src\pages\**.md i18n\en-GB\docusaurus-plugin-content-pages\
copy src\pages\**.mdx i18n\en-US\docusaurus-plugin-content-pages\

::Arabic
yarn run write-translations -- --locale ar
mkdir i18n\ar\docusaurus-plugin-content-docs\current\
copy docs\** i18n\ar\docusaurus-plugin-content-docs\current\
mkdir i18n\ar\docusaurus-plugin-content-blog\
copy blog\** i18n\ar\docusaurus-plugin-content-blog\
mkdir i18n\ar\docusaurus-plugin-content-pages\
copy src\pages\**.md i18n\ar\docusaurus-plugin-content-pages\
copy src\pages\**.mdx i18n\ar\docusaurus-plugin-content-pages\

::English (USA)
yarn run write-translations -- --locale en-US
mkdir i18n\en-US\docusaurus-plugin-content-docs\current\
copy docs\** i18n\en-US\docusaurus-plugin-content-docs\current\
mkdir i18n\en-US\docusaurus-plugin-content-blog\
copy blog\** i18n\en-US\docusaurus-plugin-content-blog\
mkdir i18n\en-US\docusaurus-plugin-content-pages\
copy src\pages\**.md i18n\en-US\docusaurus-plugin-content-pages\
copy src\pages\**.mdx i18n\en-US\docusaurus-plugin-content-pages\









::LANG
::yarn run write-translations -- --locale LANG
::copy docs\** i18n\LANG\docusaurus-plugin-content-docs\current
::copy blog\** i18n\LANG\docusaurus-plugin-content-blog
::copy src\pages\**.md i18n\LANG\docusaurus-plugin-content-pages
::copy src\pages\**.mdx i18n\LANG\docusaurus-plugin-content-pages

::English (GB)
yarn run write-translations -- --locale en-GB
copy docs\** i18n\en-GB\docusaurus-plugin-content-docs\current\
copy blog\** i18n\en-US\docusaurus-plugin-content-blog\
copy src\pages\**.md i18n\en-GB\docusaurus-plugin-content-pages\
copy src\pages\**.mdx i18n\en-US\docusaurus-plugin-content-pages\

::Arabic
yarn run write-translations -- --locale ar
copy docs\** i18n\ar\docusaurus-plugin-content-docs\current\
copy blog\** i18n\ar\docusaurus-plugin-content-blog\
copy src\pages\**.md i18n\ar\docusaurus-plugin-content-pages\
copy src\pages\**.mdx i18n\ar\docusaurus-plugin-content-pages\

::English (USA)
yarn run write-translations -- --locale en-US
copy docs\** i18n\en-US\docusaurus-plugin-content-docs\current\
copy blog\** i18n\en-US\docusaurus-plugin-content-blog\
copy src\pages\**.md i18n\en-US\docusaurus-plugin-content-pages\
copy src\pages\**.mdx i18n\en-US\docusaurus-plugin-content-pages\
