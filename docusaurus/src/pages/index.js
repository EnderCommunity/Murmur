import React from 'react';
import clsx from 'clsx';
import Layout from '@theme/Layout';
import Link from '@docusaurus/Link';
import useDocusaurusContext from '@docusaurus/useDocusaurusContext';
import styles from './index.module.css';
import Translate, {translate} from '@docusaurus/Translate';
import HomepageFeatures from '../components/HomepageFeatures';

//import Translate, {translate} from '@docusaurus/Translate';

function HomepageHeader() {
  const {siteConfig} = useDocusaurusContext();

  siteConfig.themeConfig.announcementBar.content = translate({
    id: 'website.announcement',
    message: "Please note that Mur is still in the pre-alpha development stages! (It's not functional yet)",
  })

  siteConfig.title = translate({
    id: 'homepage.header.title',
    message: 'Murmur',
  });

  siteConfig.tagline = translate({
    id: 'homepage.header.desc',
    message: 'Made by the community, for the community.',
  });

  return (
    <header className={clsx('hero hero--primary', styles.heroBanner)}>
      <div className="container">
        <h1 className="hero__title">{siteConfig.title}</h1>
        <p className="hero__subtitle">{siteConfig.tagline}</p>
        <div className={styles.buttons}>
          <Link
            className="button button--secondary button--lg"
            to="/docs/intro">
              <Translate id="homepage.header.mainbutton">Read The Docs</Translate>
          </Link>
        </div>
      </div>
    </header>
  );
}

export default function Home() {
  const {siteConfig} = useDocusaurusContext();

  siteConfig.description = translate({
    id: 'website.description',
    message: 'A completely open-source, object-oriented, and type-strict programming language.',
  });

  return (
    <Layout
      title={
          siteConfig.tagline
      }
      description={
          siteConfig.description
      }>
      <HomepageHeader />
      <main>
        <HomepageFeatures />
      </main>
    </Layout>
  );
}