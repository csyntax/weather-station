import { Component, AfterViewInit } from '@angular/core';
import { AngularFireDatabase } from '@angular/fire/database';

import { Observable } from 'rxjs';
import { map } from 'rxjs/operators';

import * as moment from 'moment';

@Component({
    selector: 'app-root',
    templateUrl: './app.component.html',
    styleUrls: ['./app.component.css']
})
export class AppComponent implements AfterViewInit {
    weatherRef!: Observable<any[]>;
    weatherData: any;
    displayedColumns: string[] = ['id', 'temp', 'press', 'hum', 'voc', 'co2'];

    constructor(private afDatabase: AngularFireDatabase) {}

    ngAfterViewInit(): void {
        this.weatherRef = this.afDatabase.list('/').snapshotChanges();

        this.weatherRef.pipe(
            map(changes =>
                changes.map(c =>
                    ({
                        key: c.payload.key,
                        data: c.payload.val()
                    })
                )
            ),
            map(data => data.sort((a, b) =>  moment.utc(b.key, 'YYYY-MM-DD-HH-mm-ss').diff(moment.utc(a.key, 'YYYY-MM-DD-HH-mm-ss'))  ))
        ).subscribe(weather => this.weatherData = weather);
    }
}
