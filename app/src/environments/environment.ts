// This file can be replaced during build by using the `fileReplacements` array.
// `ng build --prod` replaces `environment.ts` with `environment.prod.ts`.
// The list of file replacements can be found in `angular.json`.

const firebaseConfig = {
  apiKey: "AIzaSyC1Q3CsFUawMQE8hpmKXfuaJGc46lc5tQY",
  authDomain: "csyntax-weather-station.firebaseapp.com",
  databaseURL: "https://csyntax-weather-station-default-rtdb.firebaseio.com",
  projectId: "csyntax-weather-station",
  storageBucket: "csyntax-weather-station.appspot.com",
  messagingSenderId: "165595946236",
  appId: "1:165595946236:web:fb248feed02bc8b55f4b79",
  measurementId: "G-6TL2M2QXTG"
};

export const environment = {
  production: false,
  firebaseConfig,
};

/*
 * For easier debugging in development mode, you can import the following file
 * to ignore zone related error stack frames such as `zone.run`, `zoneDelegate.invokeTask`.
 *
 * This import should be commented out in production mode because it will have a negative impact
 * on performance if an error is thrown.
 */
// import 'zone.js/dist/zone-error';  // Included with Angular CLI.
