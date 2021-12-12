import React from 'react'
import Parallax from './Parallax'

export default class App extends React.Component {
    constructor(props) {
        super(props);

        this.parallaxRef = React.createRef();
    }
    
    render() {
        const styles = {
            fontFamily: 'Menlo-Regular, Menlo, monospace',
            fontSize: 14,
            lineHeight: '10px',
            color: 'white',
            display: 'flex', alignItems: 'center', justifyContent: 'center'
        }

        return (
            <Parallax ref={this.parallaxRef} pages={3}>

                <Parallax.Layer offset={0} speed={1} style={{ backgroundColor: '#243B4A' }} />
                <Parallax.Layer offset={1} speed={1} style={{ backgroundColor: '#805E73' }} />
                <Parallax.Layer offset={2} speed={1} style={{ backgroundColor: '#87BCDE' }} />

                <Parallax.Layer
                    offset={0}
                    speed={0.5}
                    style={styles}
                    onClick={() => this.parallaxRef.current.scrollTo(1)}>
                    Click!
                </Parallax.Layer>

                <Parallax.Layer
                    offset={1}
                    speed={-0.1}
                    style={styles}
                    onClick={() => this.parallaxRef.current.scrollTo(2)}>
                    Another page ...
                </Parallax.Layer>

                <Parallax.Layer
                    offset={2}
                    speed={0.5}
                    style={styles}
                    onClick={() => this.parallaxRef.current.scrollTo(0)}>
                    The end.
                </Parallax.Layer>

            </Parallax>
        )
    }
}
