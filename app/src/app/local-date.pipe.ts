import { DatePipe } from '@angular/common';
import { Pipe, PipeTransform } from '@angular/core';
import * as moment from 'moment';

@Pipe({
    name: 'localDate'
})
export class LocalDatePipe implements PipeTransform {
    transform(value: string, ...args: string[]): string {
        let output = moment(value, 'YYYY-MM-DD-HH-mm-ss').format('DD/MM/YYYY HH:mm:ss');

        console.log(output);

        return output;
    }
}
