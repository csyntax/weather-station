import type { AppProps } from 'next/app'
import SSRProvider from 'react-bootstrap/SSRProvider';

import 'bootstrap/dist/css/bootstrap.min.css';

export default function MyApp(props: AppProps) {
    const { Component, pageProps } = props;

    return(
        <SSRProvider>
            <Component {...pageProps} />
        </SSRProvider>
    );
}