const lightCodeTheme = require('prism-react-renderer/themes/github');
const darkCodeTheme = require('prism-react-renderer/themes/dracula');

/** @type {import('@docusaurus/types').DocusaurusConfig} */
module.exports = {
    title: 'Murmur',
    tagline: 'An experimental programming language for everyone.',
    url: 'https://mur-lang.org',
    baseUrl: '/',
    onBrokenLinks: 'throw',
    onBrokenMarkdownLinks: 'warn',
    favicon: 'img/favicon.ico',
    organizationName: 'EnderCommunity', // Usually your GitHub org/user name.
    projectName: 'Murmur', // Usually your repo name.
    plugins: [
        [
            '@docusaurus/plugin-google-gtag',
            {
                id: 'plugin-google-gtag-mur-1',
                // other options
            },
        ],
    ],
    themeConfig: {
        gtag: {
            trackingID: 'G-6PV3DL11XQ',
            anonymizeIP: true,
        },
        hideableSidebar: true,
        colorMode: {
            defaultMode: 'dark',
            disableSwitch: true,
            respectPrefersColorScheme: true,
        },
        navbar: {
            hideOnScroll: false,
            title: 'Murmur',
            logo: {
                alt: 'Mur\'s Logo',
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
                    position: 'left',
                    to: '/downloads/',
                },
                //Search Bar
                {
                    label: 'Playground',
                    position: 'left',
                    to: '/soon/',
                },
                {
                    label: 'Feedback & Suggestions',
                    position: 'left',
                    to: '/soon/',
                },
                {
                    to: '/blog',
                    label: 'Blog',
                    position: 'left',
                },
                {
                    label: 'Help',
                    position: 'left',
                    to: '/soon/',
                },
                {
                    type: 'localeDropdown',
                    position: 'right',
                    dropdownItemsAfter: [{
                        href: '/translate/',
                        label: 'Help Us Translate',
                    }, ],
                },
                {
                    type: 'docsVersionDropdown',
                    position: 'right',
                    dropdownItemsAfter: [{
                        href: '/versions/',
                        label: 'All Versions',
                    }, ],
                },
                {
                    href: 'https://github.com/EnderCommunity/Murmur',
                    'aria-label': 'GitHub Repository',
                    position: 'right',
                    className: 'header-github-link',
                },
            ],
        },
        footer: {
            style: 'dark',
            links: [{
                    title: 'Get Started',
                    items: [{
                            label: 'Docs',
                            to: '/docs/intro',
                        },
                        {
                            label: 'Tools & Downloads',
                            href: '/downloads/',
                        },
                        {
                            label: 'Playground',
                            href: '/soon/',
                        },
                        {
                            label: 'Help',
                            href: '/soon/',
                        },
                    ],
                },
                {
                    title: 'Community',
                    items: [{
                            label: 'Twitter',
                            href: 'https://twitter.com/_EnderCommunity',
                        },
                        {
                            label: 'Discord',
                            href: 'https://discord.gg/aWBnkJpgzt',
                        },
                        {
                            label: 'Stack Overflow',
                            href: 'https://stackoverflow.com/questions/tagged/mur',
                        },
                        {
                            label: 'Feedback & Suggestions',
                            to: '/soon/',
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
                        {
                            label: 'EnderCommunity',
                            href: 'https://endercomm.net',
                        },
                    ],
                },
                {
                    title: 'Legal',
                    // Please do not remove the privacy and terms, it's a legal requirement.
                    items: [{
                            label: 'Privacy',
                            href: '/legal/privacy/',
                        },
                        {
                            label: 'Terms',
                            href: '/legal/terms/',
                        },
                        {
                            label: 'Cookie Policy',
                            href: '/legal/cookie-policy/',
                        },
                        {
                            label: "Mur's License",
                            href: '/legal/mur/license',
                        },
                    ],
                },
            ],
            copyright: `<br>Made with 💜 for everyone | Copyright © ${new Date().getFullYear()} EnderCommunity<br>This project is possible thanks to <a href="https://github.com/" target="_blank">GitHub</a>, <a href="https://infinityfree.net/" target="_blank">InfinityFree</a>, <a href="https://www.cloudflare.com/" target="_blank">Cloudflare</a>, <a href="https://fosshost.org/" target="_blank">Fosshost</a>, and you!`,
        },
        prism: {
            theme: lightCodeTheme,
            darkTheme: darkCodeTheme,
        },
        announcementBar: {
            id: 'announcementBar',
            content: "Please note that Mur is still in the pre-alpha development stages! (It's not functional yet)",
            isCloseable: false, // Defaults to `true`.
        },
    },
    presets: [
        [
            '@docusaurus/preset-classic',
            {
                docs: {
                    sidebarPath: require.resolve('./sidebars.js'),
                    editUrl: 'https://github.com/EnderCommunity/Murmur/edit/main/docusaurus/',
                    showLastUpdateAuthor: true,
                    showLastUpdateTime: true,
                    sidebarCollapsible: true,
                    sidebarCollapsed: true,
                    versions: {
                        current: {
                            label: `0.0-test.5 🚧`,
                        },
                    },
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
        locales: ['en-GB', 'ar'],
    },
};