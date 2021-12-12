import React, { useRef } from 'react';
import { Parallax, Layer } from './Parallax';

export default function App() {
    const parallaxRef = useRef(null);

    const styles = {
        fontFamily: 'Menlo-Regular, Menlo, monospace',
        fontSize: 14,
        lineHeight: '10px',
        color: 'white',
        display: 'flex', alignItems: 'center', justifyContent: 'center'
    }

    return (
        <Parallax ref={parallaxRef} pages={3}>
            <Layer offset={0} speed={1} style={{ backgroundColor: '#243B4A' }} />
            <Layer offset={1} speed={1} style={{ backgroundColor: '#805E73' }} />
            <Layer offset={2} speed={1} style={{ backgroundColor: '#87BCDE' }} />

            <Layer
                offset={0}
                speed={0.5}
                style={styles}
                onClick={() => parallaxRef.current.scrollTo(1)}>
                Click!
            </Layer>

            <Layer
                offset={1}
                speed={-0.1}
                style={styles}
                onClick={() => parallaxRef.current.scrollTo(2)}>
                Another page ...
            </Layer>

            <Layer
                offset={2}
                speed={0.5}
                style={styles}
                onClick={() => parallaxRef.current.scrollTo(0)}>
                The end.
            </Layer>
        </Parallax>
    );
}