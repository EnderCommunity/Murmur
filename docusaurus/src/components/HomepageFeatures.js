import React from 'react';
import clsx from 'clsx';
import styles from './HomepageFeatures.module.css';
import Translate, {translate} from '@docusaurus/Translate';


const FeatureList = [
  {
    title: 'Easy to Learn',
    description: (
      translate({
        message: "Mur is an object-oriented programming language. Its structure is really easy to learn, and it's consistent with its rules!"
      })
    ),
    icon: styles.homeIcons1,
  },
  {
    title: 'Open Source',
    description: (
        translate({
          message: "Mur's compiler is completely open-source, and everyone can contribute, modify, and play around with it! You're free to do whatever you want."
        })
    ),
    icon: styles.homeIcons2, //../../static/img/cloud.svg
  },
  {
    title: 'It Just Works',
    description: (
      translate({
        message: "Your users won't need to install any additional software to run your programs. Your Mur code is all compiled and prepared on your machine."
      })
    ),
    icon: styles.homeIcons3, //../../static/img/cursor.svg
  },
];

function Feature({title, description, icon}) {
  return (
    <div className={clsx('col col--4')}>
      <div className="text--center padding-horiz--md">
        <div className={icon}></div>
        <h3><>{title}</></h3>
        <p><>{description}</></p>
      </div>
    </div>
  );
}

export default function HomepageFeatures() {
  return (
    <section className={styles.features}>
      <div className="container">
        <div className="row">
          {FeatureList.map((props, idx) => (
            <Feature key={idx} {...props} />
          ))}
        </div>
      </div>
    </section>
  );
}
