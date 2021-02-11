import { NgModule } from '@angular/core';
import { MatTableModule } from '@angular/material/table';
import {MatToolbarModule} from '@angular/material/toolbar';
import { BrowserModule } from '@angular/platform-browser';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import { AngularFireModule } from '@angular/fire';

import { environment } from '../environments/environment';

import { AppComponent } from './app.component';
import { LocalDatePipe } from './local-date.pipe';

@NgModule({
    imports: [
        BrowserModule,
        AngularFireModule.initializeApp(environment.firebaseConfig),
        BrowserAnimationsModule,
        MatTableModule,
        MatToolbarModule,
    ],
    declarations: [AppComponent, LocalDatePipe],
    bootstrap: [AppComponent]
})
export class AppModule { }
