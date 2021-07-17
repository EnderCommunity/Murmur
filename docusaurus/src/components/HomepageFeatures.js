import React from 'react';
import clsx from 'clsx';
import styles from './HomepageFeatures.module.css';
import Translate, {translate} from '@docusaurus/Translate';

import ScrollAnimation from 'react-animate-on-scroll';

import img1 from '../../static/img/code1.png';
import img2 from '../../static/img/githubdark.png';
import img3 from '../../static/img/exp.png';


const FeatureList = [
  {
    title: (
      translate({
        id: 'homepage.features.first.title',
        message: "Easy to Learn",
      })
    ),
    description: (
      translate({
        id: 'homepage.features.first.desc',
        message: "Mur is an object-oriented programming language. Its structure is really easy to learn, and it's consistent with its rules!"
      })
    ),
    icon: styles.homeIcons1,
    right: false,
    style: styles.homePageShowcase1,
    image: img1,
    anim: styles.fadeIn1,
  },
  {
    title: (
      translate({
        id: 'homepage.features.second.title',
        message: "Open Source",
      })
    ),
    description: (
        translate({
          id: 'homepage.features.second.desc',
          message: "Mur's compiler is completely open-source, and everyone can contribute, modify, and play around with it! You're free to do whatever you want."
        })
    ),
    icon: styles.homeIcons2, //../../static/img/cloud.svg
    right: true,
    style: styles.homePageShowcase2,
    image: img2,
    anim: styles.fadeIn2,
  },
  {
    title: (
      translate({
        id: 'homepage.features.third.title',
        message: "It Just Works",
      })
    ),
    description: (
      translate({
        id: 'homepage.features.third.desc',
        message: "Your users won't need to install any additional software to run your programs. Your Mur code is all compiled and prepared on your machine."
      })
    ),
    icon: styles.homeIcons3, //../../static/img/cursor.svg
    right: false,
    style: styles.homePageShowcase3,
    image: img3,
    anim: styles.fadeIn3,
  },
];

function Feature({title, description, icon}) {
  return (
    <div className={clsx('col col--5')}>
      <div className="text--center padding-horiz--md">
        <div className={icon}></div>
        <h3><>{title}</></h3>
        <p><>{description}</></p>
      </div>
    </div>
  );
}

export function OrderElms(props, idx){
  return (props.right) ? (
    <>
      <img src={props.image} className={props.style}/>
      <Feature key={idx} {...props} />
    </>
  ) : (
    <>
      <Feature key={idx} {...props} />
      <img src={props.image} className={props.style}/>
    </>
  )
}

export default function HomepageFeatures() {
  return (
    <>
      {FeatureList.map((props, idx) => (
        <section name="featuresection" className={(props.right) ? styles.features2 : styles.features}>
          <div className="container">
            <ScrollAnimation duration={0.4} animateIn={props.anim} animateOnce={true} animatePreScroll={true} className={styles.anim}>
              <div className="row">
                {OrderElms(props, idx)}
              </div>
            </ScrollAnimation>
          </div>
        </section>
      ))}
    </>
  );
}
