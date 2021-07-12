const lightCodeTheme = require('prism-react-renderer/themes/github');
const darkCodeTheme = require('prism-react-renderer/themes/dracula');

/** @type {import('@docusaurus/types').DocusaurusConfig} */
module.exports = {
    title: 'Murmur',
    tagline: 'An experimental programming language for everyone.',
    url: 'https://murmur.org',
    baseUrl: '/murmur-test/',
    onBrokenLinks: 'throw',
    onBrokenMarkdownLinks: 'warn',
    favicon: 'img/favicon.ico',
    organizationName: 'EnderCommunity', // Usually your GitHub org/user name.
    projectName: 'Murmur', // Usually your repo name.
    themeConfig: {
        colorMode: {
            defaultMode: 'dark',
            disableSwitch: true,
            respectPrefersColorScheme: true,
        },
        navbar: {
            title: 'Murmur',
            logo: {
                alt: 'Murmur\'s Logo',
                src: 'img/logo.svg',
            },
            items: [{
                    type: 'doc',
                    docId: 'intro',
                    position: 'left',
                    label: 'Docs',
                },
                {
                    label: 'Tools & Downloads',
                    position: 'left'
                },
                //Search Bar
                {
                    label: 'Playground',
                    position: 'left'
                },
                {
                    to: '/blog',
                    label: 'Blog',
                    position: 'left'
                },
                {
                    label: 'Help',
                    position: 'left'
                },
                {
                    href: 'https://github.com/EnderCommunity/Murmur',
                    label: 'GitHub',
                    position: 'right',
                },
                {
                    type: 'localeDropdown',
                    position: 'right',
                },
                {
                    type: 'docsVersionDropdown',
                    position: 'right',
                },
            ],
        },
        footer: {
            style: 'dark',
            links: [{
                    title: 'Docs',
                    items: [{
                        label: 'Docs',
                        to: '/docs/intro',
                    }, ],
                },
                {
                    title: 'Community',
                    items: [{
                            label: 'Stack Overflow',
                            href: 'https://stackoverflow.com/questions/tagged/mur',
                        },
                        {
                            label: 'Discord',
                            href: 'https://afwa.fawf.awfa',
                        },
                        {
                            label: 'Twitter',
                            href: 'https://twitter.com/EnderCommunity',
                        },
                    ],
                },
                {
                    title: 'More',
                    items: [{
                            label: 'Blog',
                            to: '/blog',
                        },
                        {
                            label: 'GitHub',
                            href: 'https://github.com/EnderCommunity/Murmur',
                        },
                    ],
                },
            ],
            copyright: `<br>Made with 💜 in Palestine | Copyright © ${new Date().getFullYear()} EnderCommunity`,
        },
        prism: {
            theme: lightCodeTheme,
            darkTheme: darkCodeTheme,
        },
        announcementBar: {
            id: 'announcementBar',
            content: 'Please note that Mur is still in the pre-alpha development stages! (It\'s not functional yet)',
            isCloseable: false, // Defaults to `true`.
        },
    },
    presets: [
        [
            '@docusaurus/preset-classic',
            {
                docs: {
                    sidebarPath: require.resolve('./sidebars.js'),
                    // Please change this to your repo.
                    editUrl: 'https://github.com/EnderCommunity/Murmur/edit/main/docusaurus/',
                },
                blog: {
                    showReadingTime: true,
                    // Please change this to your repo.
                    editUrl: 'https://github.com/EnderCommunity/Murmur/edit/main/docusaurus/',
                },
                theme: {
                    customCss: require.resolve('./src/css/custom.css'),
                },
            },
        ],
    ],
    i18n: {
        defaultLocale: 'en-GB',
        locales: ['en-GB', 'en-US', 'ar'],
    },
};