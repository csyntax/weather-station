import { NgModule } from '@angular/core';
import { MatTableModule } from '@angular/material/table';
import { MatToolbarModule } from '@angular/material/toolbar';
import { MatPaginatorModule } from '@angular/material/paginator';
import { MatDialogModule } from '@angular/material/dialog';
import { MatButtonModule } from '@angular/material/button';

import { AngularFireModule } from '@angular/fire';
import { BrowserModule } from '@angular/platform-browser';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';

import { environment } from '../environments/environment';

import { AppComponent } from './app.component';
import { LocalDatePipe } from './local-date.pipe';
import { AboutComponent } from './about/about.component';

@NgModule({
    imports: [
        BrowserModule,
        AngularFireModule.initializeApp(environment.firebaseConfig),
        BrowserAnimationsModule,
        MatTableModule,
        MatToolbarModule,
        MatPaginatorModule,
        MatButtonModule,
        MatDialogModule,
    ],
    declarations: [AppComponent, LocalDatePipe, AboutComponent],
    bootstrap: [AppComponent]
})
export class AppModule { }
