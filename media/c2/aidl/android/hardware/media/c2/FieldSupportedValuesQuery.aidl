/*
 * Copyright (C) 2022 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package android.hardware.media.c2;

import android.hardware.media.c2.ParamField;

/**
 * Query information for supported values of a field. This is used as input to
 * IConfigurable::querySupportedValues().
 */
@VintfStability
parcelable FieldSupportedValuesQuery {
    @VintfStability
    @Backing(type="int")
    enum Type {
        /**
         * Query all possible values regardless of other settings.
         */
        POSSIBLE = 0,
        /**
         * Query currently possible values given dependent settings.
         */
        CURRENT,
    }
    /**
     * Identity of the field to query.
     */
    ParamField field;
    /**
     * Type of the query. See #Type for more information.
     */
    Type type;
}
